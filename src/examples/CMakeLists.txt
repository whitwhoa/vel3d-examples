cmake_minimum_required(VERSION 3.16.0)


set(PROJECT_NAME vel3d_examples)
project(${PROJECT_NAME})


file(GLOB_RECURSE sources CONFIGURE_DEPENDS 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(${PROJECT_NAME} ${sources})
add_dependencies(${PROJECT_NAME} VEL3D_LIBRARY)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
if(MSVC)
	set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../")
endif()


target_include_directories(${PROJECT_NAME} PUBLIC
	${VEL3D_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${BULLET_INCLUDE_DIR}
	${JSON_INCLUDE_DIR}
	${IMGUI_INCLUDE_DIR}
)


if(MSVC)
	target_link_libraries(${PROJECT_NAME} PUBLIC VEL3D_LIBRARY)
else()
	target_link_libraries(${PROJECT_NAME} PUBLIC VEL3D_LIBRARY X11 Xrandr Xinerama Xxf86vm Xcursor GL dl pthread)
	# do not remember why this is here...
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
endif()
