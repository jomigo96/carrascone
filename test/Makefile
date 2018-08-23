CC=g++
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE=main

SOURCES=$(wildcard *.cpp)
OBJECTS=$(notdir $(SOURCES:.cpp=.o))
DOCDIR=../doc


tiletype: 
	g++  $(CPPFLAGS) -o TileType.o TileType.cpp
	g++  $(CPPFLAGS) -o main.o TileTypeTest.cpp
	g++ TileType.o main.o $(LDFLAGS) -o main 
	
clean:
	rm -rf $(OBJECTS) main.o $(EXECUTABLE) $(DOCDIR)/html $(DOCDIR)/latex

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all doc clean
