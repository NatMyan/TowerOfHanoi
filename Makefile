CC=g++
CFLAGS=-c -Wall
TARGET=Hanoi

SRC=$(shell find $(src) -name '*.cpp')
OBJ=$(patsubst %.cpp, %.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lncurses

%.o : %.cpp
	$(CC) -c $< -o $@

clean:
	rm -rf $(shell find $(src) -name '*.o') *.o