CC=g++
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lm -lboost_program_options
EXECUTABLE=main
DOCC=doxygen

SOURCES=$(wildcard *.cpp)
OBJECTS=$(notdir $(SOURCES:.cpp=.o))
DOCDIR=../doc


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cc.o:
	$(CC) $(CPPFLAGS) -o $@

doc:
	$(DOCC) Doxyfile

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) $(DOCDIR)/html $(DOCDIR)/latex

run: $(EXECUTABLE)
	./$(EXECUTABLE)

memcheck: $(EXECUTABLE)
	valgrind --leak-check=full --show-leak-kinds=all ./$<


.PHONY: all doc clean memcheck
