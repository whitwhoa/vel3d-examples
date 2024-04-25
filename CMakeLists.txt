cmake_minimum_required(VERSION 3.16.0)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# CMAKE_BUILD_TYPE is one of these:
# Debug, Release, RelWithDebInfo and MinSizeRel


########################################################################
# Define our project name
########################################################################
set(PROJECT_NAME vel3d_examples)
project(${PROJECT_NAME})


########################################################################
# Deduce what target we're building for
########################################################################
if(WIN32)
    set(TARGET_OS "windows")
	add_definitions(-DWINDOWS_BUILD)
elseif(UNIX AND NOT APPLE)
    if(CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(TARGET_OS "linux")
		add_definitions(-DLINUX_BUILD)
    endif()
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(TARGET_ARCH "amd64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(TARGET_ARCH "x86")
endif()


########################################################################
# Get options from user
########################################################################
option(DISPLAY_DEBUG_OUTPUT "Turn on during development. Will give useful messages as to where certain problems exist. Turn off for production" ON)
if(DISPLAY_DEBUG_OUTPUT)
	add_definitions(-DDEBUG_LOG)
endif()

option(USE_NVIDIA_API "Whether or not to utilize nvidia api library. You must include this manually within /external, and this is only for windows builds" OFF)



########################################################################
# Microsoft compiler specific configuration
########################################################################
if(MSVC)
	
	# conditionally select the appropriate runtime library: MT|MTd
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	
	#TODO: not sure this is required anymore, test to verify once everything done and working
	add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd> 
        $<$<CONFIG:Release>:/MT>
		$<$<CXX_COMPILER_ID:MSVC>:/MP>
    )
	
endif()


########################################################################
# Include required cmake modules and some GLOBALS
########################################################################
include(ExternalProject)
include(FetchContent)
set(DEP_CMAKE_PATH ${CMAKE_CURRENT_BINARY_DIR}/external)
set(DEP_INSTALL_ROOT ${CMAKE_CURRENT_BINARY_DIR}/external/installs)
set(FETCHCONTENT_BASE_DIR ${DEP_CMAKE_PATH})
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(INSTALL_ROOT ${CMAKE_CURRENT_BINARY_DIR}/installs)


########################################################################
# Install External Dependencies
########################################################################
include(glfw)
add_subdirectory(external/glad)
include(glm)
include(assimp)
include(bullet)
include(json)
include(stb)
include(imgui)
if(MSVC AND USE_NVIDIA_API)
	add_subdirectory(external/nvapi)
endif()


########################################################################
# Install Vel3D library
########################################################################
add_subdirectory(src/vel3d)


########################################################################
# Build Executables
########################################################################
add_subdirectory(src/examples)