CXX = g++
CXX_FLAGS = -g -Wall -std=c++20

OS := $(shell uname)

LINUX_INCLUDES = -I/usr/include/SFML
LINUX_LIBS = -L/usr/lib/x86_64-linux-gnu -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC = ${wildcard src/*.cpp} ${wildcard src/states/*.cpp}
OBJ = ${wildcard build/*}


INCLUDES = $(LINUX_INCLUDES)
LIBS = $(LINUX_LIBS)


all:
	${CXX} ${CXX_FLAGS} ${INCLUDES} ${SRC} main.cpp -o build/main ${LIBS}

#test:
#	${CXX} ${CXX_FLAGS} ${SRC} tests/test_board.cpp -o build/tests ${LIBS}

ferdek_tests:
	${CXX} ${CXX_FLAGS} ${SRC} tests/ferdek_tests.cpp -o build/ferdek_tests ${LIBS}

tile_tests:
	${CXX} ${CXX_FLAGS} ${SRC} tests/tile_tests.cpp -o build/tile_tests ${LIBS}

window_tests:
	${CXX} ${CXX_FLAGS} ${SRC} tests/window_tests.cpp -o build/window_tests ${LIBS}

managers_tests:
	${CXX} ${CXX_FLAGS} ${SRC} tests/managers_tests.cpp -o build/managers_tests ${LIBS}

mob_tests:
	${CXX} ${CXX_FLAGS} ${SRC} tests/mob_tests.cpp -o build/mob_tests ${LIBS}


clean: ${OBJ}
	@echo "Removing ${OBJ}"
	rm -f ${OBJ}
