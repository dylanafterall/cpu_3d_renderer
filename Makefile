# -*- MakeFile -*-

#target:dependencies
#   action

#INCLUDE_PATHS = -I/usr/local/Cellar/sdl2/2.0.20/include -I/usr/local/Cellar/sdl2_image/2.0.5/include
#LIBRARY_PATHS = -L/usr/local/Cellar/sdl2/2.0.20/lib -L/usr/local/Cellar/sdl2_image/2.0.5/lib

SRC_DIR = src
BUILD_DIR = build/debug
CC = gcc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_NAME = renderer
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llib
COMPILER_FLAGS = -std=c99 -Wall -O0 -g
LINKER_FLAGS = -lSDL2 -lm

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

run:
	./build/debug/renderer
clean:
	rm ./build/debug/renderer