if(NOT DEP_CMAKE_PATH OR NOT DEP_INSTALL_ROOT)
  message(FATAL_ERROR "DEP_CMAKE_PATH and DEP_INSTALL_ROOT must be set before including modules defined within /external")
endif()

########################################################################
# SETUP IMGUI
########################################################################
set(libImGui imgui)
FetchContent_Declare(${libImGui}
	GIT_REPOSITORY https://github.com/ocornut/imgui.git
	GIT_TAG v1.90.1
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
)

FetchContent_GetProperties(${libImGui})
if(NOT ${libImGui})
  FetchContent_Populate(${libImGui})
endif()

file(
COPY
	${${libImGui}_SOURCE_DIR}/imgui_demo.cpp
	${${libImGui}_SOURCE_DIR}/imgui.cpp
	${${libImGui}_SOURCE_DIR}/imgui_draw.cpp
	${${libImGui}_SOURCE_DIR}/imgui_tables.cpp
	${${libImGui}_SOURCE_DIR}/imgui_widgets.cpp
	${${libImGui}_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
	${${libImGui}_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
DESTINATION
	${DEP_INSTALL_ROOT}/${libImGui}/src
)

file(
COPY
	${${libImGui}_SOURCE_DIR}/imconfig.h
	${${libImGui}_SOURCE_DIR}/imgui.h
	${${libImGui}_SOURCE_DIR}/imgui_internal.h
	${${libImGui}_SOURCE_DIR}/imstb_rectpack.h
	${${libImGui}_SOURCE_DIR}/imstb_textedit.h
	${${libImGui}_SOURCE_DIR}/imstb_truetype.h
	${${libImGui}_SOURCE_DIR}/backends/imgui_impl_glfw.h
	${${libImGui}_SOURCE_DIR}/backends/imgui_impl_opengl3.h
	${${libImGui}_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h
DESTINATION
	${DEP_INSTALL_ROOT}/${libImGui}/include/${libImGui}
)

file(GLOB_RECURSE imgui_headers CONFIGURE_DEPENDS "${DEP_INSTALL_ROOT}/${libImGui}/include/${libImGui}/*.h")
file(GLOB_RECURSE imgui_sources CONFIGURE_DEPENDS "${DEP_INSTALL_ROOT}/${libImGui}/src/*.cpp")
add_library(IMGUI_LIBRARY STATIC ${imgui_headers} ${imgui_sources})
add_dependencies(IMGUI_LIBRARY ${libGLFW})

set_target_properties(IMGUI_LIBRARY PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${DEP_INSTALL_ROOT}/${libImGui}/lib
)

target_include_directories(IMGUI_LIBRARY
	PUBLIC ${DEP_INSTALL_ROOT}/${libImGui}/include/${libImGui}
	PUBLIC ${DEP_INSTALL_ROOT}/${libGLFW}/include
)

set(IMGUI_INCLUDE_DIR ${DEP_INSTALL_ROOT}/${libImGui}/include)