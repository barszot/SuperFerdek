CXX = g++
CXX_FLAGS = -g -Wall -std=c++20

OS := $(shell uname)

LINUX_INCLUDES = -I/usr/include/SFML
LINUX_LIBS = -L/usr/lib/x86_64-linux-gnu -lsfml-graphics -lsfml-window -lsfml-system

SRC = ${wildcard src/*.cpp} ${wildcard src/states/*.cpp}
OBJ = ${wildcard build/*}


INCLUDES = $(LINUX_INCLUDES)
LIBS = $(LINUX_LIBS)


all:
	${CXX} ${CXX_FLAGS} ${INCLUDES} ${SRC} main.cpp -o build/main ${LIBS}

test:
	${CXX} ${CXX_FLAGS} ${SRC} tests/test_board.cpp -o build/tests ${LIBS}

clean: ${OBJ}
	@echo "Removing ${OBJ}"
	rm -f ${OBJ}
