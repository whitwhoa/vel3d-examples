cmake_minimum_required(VERSION 3.16.0)

if(NOT DEP_CMAKE_PATH OR NOT DEP_INSTALL_ROOT)
  message(FATAL_ERROR "DEP_CMAKE_PATH and DEP_INSTALL_ROOT must be set before including modules defined within /external")
endif()


file(GLOB_RECURSE khr_headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/*.h")
file(GLOB_RECURSE glad_headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/*.h")
file(GLOB_RECURSE glad_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

file(
COPY
	${CMAKE_CURRENT_SOURCE_DIR}/include/glad
DESTINATION
	${DEP_INSTALL_ROOT}/glad/include
)

file(
COPY
	${CMAKE_CURRENT_SOURCE_DIR}/include/KHR
DESTINATION
	${DEP_INSTALL_ROOT}/glad/include
)

add_library(GLAD_LIBRARY STATIC ${khr_headers} ${glad_headers} ${glad_sources})

set_target_properties(GLAD_LIBRARY PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${DEP_INSTALL_ROOT}/glad/lib
)

target_include_directories(GLAD_LIBRARY PUBLIC
	${DEP_INSTALL_ROOT}/glad/include
)

set(GLAD_INCLUDE_DIR ${DEP_INSTALL_ROOT}/glad/include PARENT_SCOPE)