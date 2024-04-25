if(NOT DEP_CMAKE_PATH OR NOT DEP_INSTALL_ROOT)
  message(FATAL_ERROR "DEP_CMAKE_PATH and DEP_INSTALL_ROOT must be set before including modules defined within /external")
endif()

########################################################################
# Install nlohmann/json
########################################################################
set(libJson json)
FetchContent_Declare(${libJson}
	GIT_REPOSITORY https://github.com/nlohmann/json.git
	GIT_TAG v3.11.3
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	SOURCE_DIR 
)

FetchContent_GetProperties(${libJson})
if(NOT ${libJson})
  FetchContent_Populate(${libJson})
endif()

add_library(${libJson} INTERFACE)

file(
COPY
	${${libJson}_SOURCE_DIR}/single_include/nlohmann/json.hpp
DESTINATION
	${DEP_INSTALL_ROOT}/${libJson}/include/nlohmann
)

set(JSON_INCLUDE_DIR ${DEP_INSTALL_ROOT}/${libJson}/include)