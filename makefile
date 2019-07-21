
EVENTSRC = Event/EventDispatcher.cpp Event/EventListener.cpp 
GUIEP = GUI/Elements
GUIESRC = $(GUIEP)/Button.cpp $(GUIEP)/SwitchButton.cpp
GUISRC = GUI/Gui.cpp GUI/GuiElement.cpp GUI/Auxiliary/Auxiliary.cpp $(GUIESRC)

FSMSRC= Tetris.cpp Menu.cpp

SRC = main.cpp Game.cpp States.cpp Style.cpp $(FSMSRC) $(EVENTSRC) $(GUISRC)
OBJ = $(SRC:.cpp=.o)	
NAME = Tetrines
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBPATH = /usr/lib/x86_64-linux-gnu

all:
	@echo "make install for start installation"

install: build rmo

build: $(OBJ)
	@g++ -g -Wall $(OBJ) -L$(LIBPATH) $(LIBS) -o $(NAME) && echo compile : succes

.cpp.o:
	g++ -g -c -Wall -I./ $< -o $@

rmo: 
	@find ./ -name "*.o" | xargs rm && echo object remove : succes