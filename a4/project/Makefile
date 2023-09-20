CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
OBJECTS = model/model.o model/gameRunner.o view/view.o view/cursesView.o object/interactableObject.o object/pixel.o object/frame.o object/gameObject.o object/status.o behaviours/behaviour.o controller/cursesControl.o controller/controller.o
GAME = main.o
GAME1 = main1.o
GAME2 = main2.o
DEPENDS = ${OBJECTS:.o=.d}
GAME_DEPENDS = ${GAME:.o=.d}
GAME1_DEPENDS = ${GAME1:.o=.d}
GAME2_DEPENDS = ${GAME2:.o=.d}

all: game1 game2 game3

game1: ${OBJECTS} ${GAME1}
	${CXX} ${OBJECTS} ${GAME1} -lncurses -o game1

-include ${DEPENDS} ${GAME1_DEPENDS}

game2: ${OBJECTS} ${GAME2}
	${CXX} ${OBJECTS} ${GAME2} -lncurses -o game2

-include ${DEPENDS} ${GAME2_DEPENDS}

game3: ${OBJECTS} ${GAME}
	${CXX} ${OBJECTS} ${GAME} -lncurses -o game3

-include ${DEPENDS} ${GAME_DEPENDS}
.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC} ${GAME1} ${GAME2}
