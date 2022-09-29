cmake_minimum_required(VERSION 3.15)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# project name
project(myjgs LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# global include
include_directories(${PROJECT_SOURCE_DIR}/3rdParts/meojson/include) #header-only json lib

add_subdirectory(utils)
add_subdirectory(src)
add_subdirectory(test)

add_dependencies(myjgs config)
add_dependencies(test myjgs config)