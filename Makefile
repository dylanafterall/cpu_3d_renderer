#    Dylan Campbell
#    dyl@mailbox.org
#    3D Graphics Renderer in C

#------------------------------------------------------------------------------
# make					makes renderer executable
# make run				runs renderer executable
# make clean			removes all binaries (.o, debug, executable)
#------------------------------------------------------------------------------

SRC_DIR = src
INC_DIR = include
OBJ_DIR = build
BIN_DIR = bin
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(wildcard $(OBJ_DIR)/*.o)
CC = gcc
BIN_NAME = renderer
INCLUDE_PATHS =
LIBRARY_PATHS =
COMPILER_FLAGS = -std=c99 -Wall
LINKER_FLAGS = -lSDL2 -lm

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(SRC_FILES) -o $(BIN_DIR)/$(BIN_NAME)

run:
	./bin/renderer
clean:
	rm ./bin/renderer