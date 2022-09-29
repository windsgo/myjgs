add_executable(test test.cpp) # add excutable : test, with the found source files
target_include_directories(test PRIVATE ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/utils) # set include dir
target_link_libraries(test config myjgs)