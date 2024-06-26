cmake_minimum_required(VERSION 3.16.0)

if(NOT DEP_CMAKE_PATH OR NOT DEP_INSTALL_ROOT)
  message(FATAL_ERROR "DEP_CMAKE_PATH and DEP_INSTALL_ROOT must be set before including modules defined within /external")
endif()


file(
COPY
	${CMAKE_CURRENT_SOURCE_DIR}/bin/${TARGET_OS}_${TARGET_ARCH}_Release/${CMAKE_STATIC_LIBRARY_PREFIX}nvapi64${CMAKE_STATIC_LIBRARY_SUFFIX}
DESTINATION
	${DEP_INSTALL_ROOT}/nvapi/lib
)

file(
COPY
	${CMAKE_CURRENT_SOURCE_DIR}/include/nvapi
DESTINATION
	${DEP_INSTALL_ROOT}/nvapi/include
)


add_library(NVAPI_LIBRARY STATIC IMPORTED GLOBAL)
set_target_properties(NVAPI_LIBRARY PROPERTIES IMPORTED_LOCATION ${DEP_INSTALL_ROOT}/nvapi/lib/${CMAKE_STATIC_LIBRARY_PREFIX}nvapi64${CMAKE_STATIC_LIBRARY_SUFFIX})
set(NVAPI_INCLUDE_DIR ${DEP_INSTALL_ROOT}/nvapi/include PARENT_SCOPE)