CXX = g++
CXXFLAGS = -std=c++14 -Werror -MMD -lncurses -g
EXEC = maze
OBJECTS = curseControl.o curseView.o keyboard.o  main.o  maze.o  model.o  standard.o controller.o writtenView.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${GIVEN} -o ${EXEC} ${CXXFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
