cmake_minimum_required(VERSION 3.15)

# project name
project(myjgs LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)

# global include
include_directories(${PROJECT_SOURCE_DIR}/3rdParts/meojson/include) #header-only json lib

add_subdirectory(utils)

# test
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

aux_source_directory(${SRC_DIR} SRC_FILE) # find all source files
add_executable(test ${SRC_FILE}) # add excutable : test, with the found source files
target_include_directories(test PUBLIC ${SRC_DIR} ${PROJECT_SOURCE_DIR}/utils) # set include dir
target_link_libraries(test config)

add_dependencies(test config)