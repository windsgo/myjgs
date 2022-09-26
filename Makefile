SRC=test.cpp block.cpp event.cpp item.cpp type.cpp

TARGET=a.out

default: all

all:${SRC}
	g++ ${SRC} -std=c++17 -o ${TARGET}

run: all
	./${TARGET}