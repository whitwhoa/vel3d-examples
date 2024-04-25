if(NOT DEP_CMAKE_PATH OR NOT DEP_INSTALL_ROOT)
  message(FATAL_ERROR "DEP_CMAKE_PATH and DEP_INSTALL_ROOT must be set before including modules defined within /external")
endif()

########################################################################
# Install GLM
########################################################################
set(libGLM glm)
ExternalProject_Add(${libGLM}
PREFIX			${DEP_CMAKE_PATH}/${libGLM}
GIT_REPOSITORY  https://github.com/g-truc/glm.git
GIT_TAG         origin/master
GIT_SHALLOW     ON
UPDATE_COMMAND 	""
CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${DEP_INSTALL_ROOT}/${libGLM}
				-DBUILD_SHARED_LIBS:BOOL=OFF
				-DBUILD_STATIC_LIBS:BOOL=OFF
				-DGLM_TEST_ENABLE:BOOL=OFF
)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
set(GLM_INCLUDE_DIR ${DEP_INSTALL_ROOT}/${libGLM}/include)