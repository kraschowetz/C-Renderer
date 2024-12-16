COMPILER = gcc
FLAGS = -Wall -Wextra -Wconversion -Wunreachable-code -Wpointer-arith -O2 
LIBS =  -lm -lcglm -Lgl -Llib -l:glad.a -lSDL2main -lSDL2

SRC = $(wildcard src/*.c) $(wildcard src/*/*.c)

OUTPUT = .
BINNAME = main

all: 
	$(COMPILER) $(SRC) -o $(OUTPUT)/$(BINNAME) $(LIBS) $(FLAGS)
