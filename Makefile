.PHONY: all clean

CXX := g++
CXX_FLAGS := -std=c++23 -ggdb -pedantic -Wall -Werror

SRC := src
INCLUDE := include
BIN := bin

LIBRARIES := 
EXECUTABLE := main

all:$(BIN)/${EXECUTABLE}


run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

${BIN}/${EXECUTABLE}:${SRC}/*.cpp ${INCLUDE}/*.h
	$(CXX) $(CXX_FLAGS) ${SRC}/*.cpp -I$(INCLUDE) -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*