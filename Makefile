CXX = g++
CXXFLAG = -Wall -DGLEW_STATIC 

SRC = $(PWD)/src/*.cpp
INCLUDE = -I $(PWD)/include
OBJ = main.o scriptManager.o game.o window.o shader.o object.o objectManager.o timer.o

LIB = -lSDL2main -lSDL2 -lGLEW -lGL -lGLU -llua5.2

OUT_EXE = pop3d 

$(OUT_EXE): $(OBJ)
	$(CXX) $(SRC) $(CXXFLAG) $(INCLUDE) $(LIB) -g -o $@

%.o: $(PWD)/src/%.cpp 
	$(CXX) $< $(CXXFLAG) $(INCLUDE) $(LIB) -c

clean:
	rm -fr *.o
