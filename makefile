# Compiler
CC=gcc
CFLAGS=-lncursesw -I $(LIBS)

MKBIN = mkdir $(BIN)
MKBUILD = mkdir $(BUILD)

# Directory Structure
BIN = bin/
BUILD = build/
LIBS = include/
SRC = src/

# Header files
_DEPS=
DEPS = $(patsubst %,$(LIBS)%,$(_DEPS))

# Object Files
_OBJ=\
	main.o \
	snake.o \
	coord.o \
	powerup.o
OBJ = $(patsubst %,$(BUILD)%,$(_OBJ))

MAIN = main

default: mkdir $(OBJ)
	$(CC) $(OBJ) -o $(addprefix $(BIN),$(MAIN)) $(CFLAGS)

$(BUILD)%.o: $(SRC)%.c
	$(CC) -c $< -o $@ $(CFLAGS)

run:
	./$(BIN)$(MAIN)

mkdir:
	$(RM) -r $(BIN)
	$(MKBIN)
	$(RM) -r $(BUILD)
	$(MKBUILD)

clean:
	$(RM) -r $(BUILD)
	$(RM) -r *~
