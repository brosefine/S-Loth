############################################################
# CMake Build Script
############################################################

# Project settings
cmake_minimum_required(VERSION 2.8.7)
project(s-loth)

set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
            "Choose the type of build, options are: None Debug Release RelWithDebInfo MinsizeRel."
            FORCE)
endif()

get_filename_component(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX} ABSOLUTE)

message(STATUS "Build type:     ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

############################################################
# Directories

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(TEST_OUTPUT_PATH ${CMAKE_BINARY_DIR}/test)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(S-LOTH_CONFIG_DIR ${CMAKE_BINARY_DIR})

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "default install path" FORCE )
endif()


file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
file(MAKE_DIRECTORY ${TEST_OUTPUT_PATH})
file(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})

############################################################
if(MSVC)
    set(PROJECT_COMPILE_FLAGS "-D_VARIADIC_MAX=10 -D _SCL_SECURE=0 -D _USE_MATH_DEFINES=1 /MP -D NOMINMAX")
    set(PROJECT_LIBS "")
elseif(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(PROJECT_COMPILE_FLAGS "-std=c++1y -Wall -pthread -fPIC -fopenmp")
    set(PROJECT_LIBS "pthread")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROJECT_COMPILE_FLAGS}")

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH "\$ORIGIN/../lib")

############################################################
# Externals
################################
SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${GLOBAL_EXT_DIR})

################################
# GLUT
################################
include(FindGLUT)

################################
# OpenGL
################################
include(FindOpenGL)

###############################
# GLEW
###############################
include(FindGLEW)

################################ 
# SOIL
################################
include(FindSOIL)

############################################################
# Targets

add_subdirectory(${CMAKE_SOURCE_DIR}/source)
add_subdirectory(${CMAKE_SOURCE_DIR}/apps)


# install shaders
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders DESTINATION resources
        FILES_MATCHING
        PATTERN "*.glsl"
        )

# install textures
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources/textures DESTINATION resources
        FILES_MATCHING
        PATTERN "*.png"
        PATTERN "*.PNG"
        PATTERN "*.jpg"
        PATTERN "*.JPG"
        PATTERN "*.jpeg"
        PATTERN "*.JPEG"
        )


