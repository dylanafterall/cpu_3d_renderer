#    Dylan Campbell
#    campbell.dyl@gmail.com
#    3D Graphics Renderer in C


SRC_DIR = ./src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
INC_DIR = ./include
LIB_DIR = ./lib
OBJ_DIR = ./obj
OBJ_FILES = $(wildcard $(OBJ_DIR)/*.o)
BIN_DIR = ./bin
TARGET = ./bin/renderer

CC = gcc
CFLAGS = -std=c99 -Wall
INC_PATH = -I$(INC_DIR) -I$(INC_DIR)/SDL2 -I$(INC_DIR)/SDL2_image
LIB_PATH = 
LIBS = -lSDL2 -lSDL2_image -lm


#------------------------------------------------------------------------------
# make                  makes renderer executable and object files
# make run              runs renderer executable
# make clean            removes all binaries (executable and object files)
#------------------------------------------------------------------------------
all: array.o display.o light.o main.o matrix.o mesh.o swap.o texture.o        \
triangle.o vector.o
	$(CC) $(CFLAGS) $(LIBS) -o $(TARGET) $(OBJ_DIR)/array.o                   \
	$(OBJ_DIR)/display.o $(OBJ_DIR)/light.o $(OBJ_DIR)/main.o                 \
	$(OBJ_DIR)/matrix.o $(OBJ_DIR)/mesh.o $(OBJ_DIR)/swap.o                   \
	$(OBJ_DIR)/texture.o $(OBJ_DIR)/triangle.o $(OBJ_DIR)/vector.o 

array.o : $(SRC_DIR)/array.c $(INC_DIR)/array.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o $(OBJ_DIR)/array.o $(SRC_DIR)/array.c

display.o : $(SRC_DIR)/display.c $(INC_DIR)/display.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o $(OBJ_DIR)/display.o $(SRC_DIR)/display.c

light.o : $(SRC_DIR)/light.c $(INC_DIR)/light.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o $(OBJ_DIR)/light.o $(SRC_DIR)/light.c

main.o : $(SRC_FILES) 
	$(CC) $(CFLAGS) $(INC_PATH) -c -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.c

matrix.o : $(SRC_DIR)/matrix.c $(INC_DIR)/matrix.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o $(OBJ_DIR)/matrix.o $(SRC_DIR)/matrix.c

mesh.o : $(SRC_DIR)/mesh.c $(INC_DIR)/mesh.h $(INC_DIR)/array.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o $(OBJ_DIR)/mesh.o $(SRC_DIR)/mesh.c

swap.o : $(SRC_DIR)/swap.c $(INC_DIR)/swap.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o $(OBJ_DIR)/swap.o $(SRC_DIR)/swap.c

texture.o : $(SRC_DIR)/texture.c $(INC_DIR)/texture.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o $(OBJ_DIR)/texture.o $(SRC_DIR)/texture.c

triangle.o : $(SRC_DIR)/triangle.c $(INC_DIR)/triangle.h $(INC_DIR)/display.h \
$(INC_DIR)/swap.h $(INC_DIR)/vector.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o $(OBJ_DIR)/triangle.o                   \
	$(SRC_DIR)/triangle.c

vector.o : $(SRC_DIR)/vector.c $(INC_DIR)/vector.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o $(OBJ_DIR)/vector.o $(SRC_DIR)/vector.c


run:
	$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ_FILES)