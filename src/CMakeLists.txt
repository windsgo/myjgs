set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

aux_source_directory(${SRC_DIR} SRC_FILE) # find all source files

add_library(myjgs STATIC ${SRC_FILE})
target_include_directories(myjgs PRIVATE ${PROJECT_SOURCE_DIR}/utils)
target_include_directories(myjgs PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(myjgs config)

file(COPY block.h game.h item.h myjgs.h player.h type.h DESTINATION ${PROJECT_BINARY_DIR}/include)