CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD -Werror=vla
EXEC = biquadris
OBJECTS = window.o block.o board.o boardManager.o cell.o controller.o level.o nextblock.o score.o view.o main.o keyController.o levelZero.o levelOne.o levelTwo.o levelThree.o levelFour.o
DEPENDS = ${OBJECTS:.o=.d}
SRC = ${OBJECTS:.o=.cc}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${SRC} -o ${EXEC} -lX11 

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean

