if(NOT DEP_CMAKE_PATH OR NOT DEP_INSTALL_ROOT)
  message(FATAL_ERROR "DEP_CMAKE_PATH and DEP_INSTALL_ROOT must be set before including modules defined within /external")
endif()

########################################################################
# Install GLFW
########################################################################
set(libGLFW glfw)
ExternalProject_Add(${libGLFW}
PREFIX			${DEP_CMAKE_PATH}/${libGLFW}
GIT_REPOSITORY  https://github.com/glfw/glfw.git
GIT_TAG         3.3.9
GIT_SHALLOW     ON
UPDATE_COMMAND 	""
CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${DEP_INSTALL_ROOT}/${libGLFW}
				-DGLFW_BUILD_DOCS:BOOL=OFF
				-DGLFW_BUILD_EXAMPLES:BOOL=OFF
				-DGLFW_BUILD_TESTS:BOOL=OFF
				-DUSE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=OFF
				-DGLFW_USE_HYBRID_HPG:BOOL=ON
)

add_library(GLFW_LIBRARY STATIC IMPORTED)
set_target_properties(GLFW_LIBRARY PROPERTIES IMPORTED_LOCATION ${DEP_INSTALL_ROOT}/${libGLFW}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX})
set(GLFW_INCLUDE_DIR ${DEP_INSTALL_ROOT}/${libGLFW}/include)