############################################################
# CMake Build Script
############################################################

# Project settings
cmake_minimum_required(VERSION 3.14)

file(GLOB_RECURSE SRC_FILES
        ${CMAKE_SOURCE_DIR}/source/src/*.cpp 
        ${CMAKE_SOURCE_DIR}/source/src/*.c)


include(FetchContent)

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

FetchContent_Declare(
        freeglut
        GIT_REPOSITORY https://github.com/LuaDist/freeglut/
)
FetchContent_MakeAvailable(freeglut)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        0.9.9.8
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
  GLEW
  URL            https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip
)
FetchContent_MakeAvailable(glew)
find_package(GLEW REQUIRED)

FetchContent_Declare(
        soil
        GIT_REPOSITORY https://github.com/paralin/soil
)
FetchContent_MakeAvailable(soil)

add_library(source_files ${SRC_FILES})
target_include_directories(source_files PUBLIC ${CMAKE_SOURCE_DIR}/source/include/ ${CMAKE_SOURCE_DIR}/lib_headers/)
target_link_libraries(source_files freeglut glm GLEW::GLEW soil)

add_executable(${PROJECT_NAME}_main ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${SRC_FILES})
target_include_directories(${PROJECT_NAME}_main PUBLIC ${CMAKE_SOURCE_DIR}/source/include/ ${CMAKE_SOURCE_DIR}/lib_headers/)
target_link_libraries(${PROJECT_NAME}_main freeglut glm GLEW::GLEW soil)