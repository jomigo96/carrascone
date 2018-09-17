CC=g++
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE=test

SOURCES=$(wildcard *.cpp)
OBJECTS=$(notdir $(SOURCES:.cpp=.o))
OBJ= *.o
DOCDIR=../doc


test: 
	$(MAKE) -C ../src
	cp ../src/TileType.o .
	cp ../src/Cell.o .
	cp ../src/Tile.o .
	$(CC)  $(CPPFLAGS) -o TileTypeTest.o TileTypeTest.cpp
	$(CC)  $(CPPFLAGS) -o TileTest.o TileTest.cpp
	$(CC)  $(CPPFLAGS) -o CellTest.o CellTest.cpp
	$(CC)  $(CPPFLAGS) -o tests-main.o tests-main.cpp
	$(CC) $(OBJ) $(LDFLAGS) -o test 
	
clean:
	rm -rf $(OBJECTS) main.o $(EXECUTABLE) $(DOCDIR)/html $(DOCDIR)/latex

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all doc clean
