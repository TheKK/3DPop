CXX = g++
CXXFLAG = -Wall -DGLEW_STATIC 

SRC = $(PWD)/src/*.cpp
INCLUDE = -I $(PWD)/include
OBJ = main.o game.o window.o shader.o object.o timer.o

LIB = -lSDL2main -lSDL2 -lGLEW -lGL -lGLU

OUT_EXE = pop3d 

$(OUT_EXE): $(OBJ)
	$(CXX) $(SRC) $(CXXFLAG) $(INCLUDE) $(LIB) -g -o $@

%.o: $(PWD)/src/%.cpp 
	$(CXX) $< $(CXXFLAG) $(INCLUDE) $(LIB) -c

clean:
	rm -fr *.o
