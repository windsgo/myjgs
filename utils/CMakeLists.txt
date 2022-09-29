

add_library(config STATIC config.cpp config.h)
file(COPY config.h DESTINATION ${PROJECT_BINARY_DIR}/include)