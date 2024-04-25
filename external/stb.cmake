if(NOT DEP_CMAKE_PATH OR NOT DEP_INSTALL_ROOT)
  message(FATAL_ERROR "DEP_CMAKE_PATH and DEP_INSTALL_ROOT must be set before including modules defined within /external")
endif()

########################################################################
# Install STB_IMAGE and STB_TRUETYPE
########################################################################
set(libStbHeaders stb_headers)
FetchContent_Declare(${libStbHeaders}
	GIT_REPOSITORY https://github.com/nothings/stb.git
	GIT_TAG origin/master
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
)

FetchContent_GetProperties(${libStbHeaders})
if(NOT ${libStbHeaders})
  FetchContent_Populate(${libStbHeaders})
endif()

add_library(${libStbHeaders} INTERFACE)

file(
COPY
	${${libStbHeaders}_SOURCE_DIR}/stb_image.h
DESTINATION
	${DEP_INSTALL_ROOT}/${libStbHeaders}/include/${libStbHeaders}
)

file(
COPY
	${${libStbHeaders}_SOURCE_DIR}/stb_truetype.h
DESTINATION
	${DEP_INSTALL_ROOT}/${libStbHeaders}/include/${libStbHeaders}
)

set(STBHEADERS_INCLUDE_DIR ${DEP_INSTALL_ROOT}/${libStbHeaders}/include)