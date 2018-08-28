CC=g++
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE=test

SOURCES=$(wildcard *.cpp)
OBJECTS=$(notdir $(SOURCES:.cpp=.o))
DOCDIR=../doc


test: 
	$(MAKE) -C ../src
	cp ../src/TileType.o .
	g++  $(CPPFLAGS) -o TileTypeTest.o TileTypeTest.cpp
	g++  $(CPPFLAGS) -o tests-main.o tests-main.cpp
	g++ TileType.o TileTypeTest.o tests-main.o $(LDFLAGS) -o test 
	
clean:
	rm -rf $(OBJECTS) main.o $(EXECUTABLE) $(DOCDIR)/html $(DOCDIR)/latex

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all doc clean
