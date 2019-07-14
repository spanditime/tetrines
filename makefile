
EVENTSRC = Event/EventDispatcher.cpp Event/EventListener.cpp 
GUISRC = GUI/Gui.cpp GUI/GuiElement.cpp

SRC = main.cpp Game.cpp Tetris.cpp States.cpp $(EVENTSRC) $(GUISRC)
OBJ = $(SRC:.cpp=.o)
NAME = Tetrines
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBPATH = /usr/lib/x86_64-linux-gnu

all: build rmo
 
build: $(OBJ)
	g++ -Wall $(OBJ) -L$(LIBPATH) $(LIBS) -o $(NAME)

.cpp.o:
	g++ -c -Wall -I./ $< -o $@

rmo:
	find ./ -name "*.o" | xargs rm