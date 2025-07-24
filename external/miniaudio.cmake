if(NOT DEP_CMAKE_PATH OR NOT DEP_INSTALL_ROOT)
  message(FATAL_ERROR "DEP_CMAKE_PATH and DEP_INSTALL_ROOT must be set before including modules defined within /external")
endif()

########################################################################
# Install MiniAudio
########################################################################
set(libMA miniaudio)
FetchContent_Declare(${libMA}
	GIT_REPOSITORY https://github.com/mackron/miniaudio.git
	GIT_TAG origin/master
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
)

FetchContent_GetProperties(${libMA})
if(NOT ${libMA})
  FetchContent_Populate(${libMA})
endif()

file(
COPY
	${${libMA}_SOURCE_DIR}/miniaudio.c
DESTINATION
	${DEP_INSTALL_ROOT}/${libMA}/src
)

file(
COPY
	${${libMA}_SOURCE_DIR}/miniaudio.h
DESTINATION
	${DEP_INSTALL_ROOT}/${libMA}/include/${libMA}
)

file(GLOB_RECURSE miniaudio_headers CONFIGURE_DEPENDS "${DEP_INSTALL_ROOT}/${libMA}/include/${libMA}/*.h")
file(GLOB_RECURSE miniaudio_sources CONFIGURE_DEPENDS "${DEP_INSTALL_ROOT}/${libMA}/src/*.c")
add_library(MINIAUDIO_LIBRARY STATIC ${miniaudio_headers} ${miniaudio_sources})

set_target_properties(MINIAUDIO_LIBRARY PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${DEP_INSTALL_ROOT}/${libMA}/lib
)

target_include_directories(MINIAUDIO_LIBRARY
	PUBLIC ${DEP_INSTALL_ROOT}/${libMA}/include/${libMA}
)

set(MINIAUDIO_INCLUDE_DIR ${DEP_INSTALL_ROOT}/${libMA}/include)