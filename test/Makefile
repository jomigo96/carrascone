CC=g++
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lm
EXECUTABLE=test
TESTCASES=../src/TileType.o ../src/Tile.o ../src/Cell.o ../src/Map.o

SOURCES=$(wildcard *.cpp)
OBJECTS=$(notdir $(SOURCES:.cpp=.o))
OBJ=*.o

$(EXECUTABLE): $(OBJECTS)
	$(MAKE) -C ../src
	cp $(TESTCASES) .
	$(CC) $(OBJ) $(LDFLAGS) -o $@ 
	
clean:
	rm -rf $(OBJ) $(EXECUTABLE) 

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all doc clean
