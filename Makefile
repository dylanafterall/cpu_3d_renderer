#    Dylan Campbell
#    campbell.dyl@gmail.com
#    3D Graphics Renderer in C


SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(wildcard obj/*.o)
INC_PATH = -Isrc/headers
TARGET = bin/renderer

CC = gcc
CFLAGS = -std=c99 -Wall
LIBS = -lSDL2 -lSDL2_image -lm


#------------------------------------------------------------------------------
# make                  makes renderer executable and object files
# make run              runs renderer executable
# make clean            removes all binaries (executable and object files)
#------------------------------------------------------------------------------
renderer: array.o camera.o clipping.o display.o light.o main.o matrix.o mesh.o \
swap.o texture.o triangle.o upng.o vector.o
	$(CC) $(CFLAGS) $(LIBS) -o $(TARGET) obj/array.o obj/camera.o obj/clipping.o \
	obj/display.o obj/light.o obj/main.o obj/matrix.o obj/mesh.o obj/swap.o \
	obj/texture.o obj/triangle.o obj/upng.o obj/vector.o 

array.o : src/array.c src/headers/array.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/array.o src/array.c

camera.o : src/camera.c src/headers/camera.h src/headers/vector.h 
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/camera.o src/camera.c

clipping.o : src/clipping.c src/headers/clipping.h src/headers/vector.h \
src/headers/triangle.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/clipping.o src/clipping.c

display.o : src/display.c src/headers/display.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/display.o src/display.c

light.o : src/light.c src/headers/light.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/light.o src/light.c

main.o : $(SRC_FILES) 
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/main.o src/main.c

matrix.o : src/matrix.c src/headers/matrix.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/matrix.o src/matrix.c

mesh.o : src/mesh.c src/headers/mesh.h src/headers/array.h \
src/headers/triangle.h  src/headers/upng.h src/headers/vector.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/mesh.o src/mesh.c

swap.o : src/swap.c src/headers/swap.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/swap.o src/swap.c

texture.o : src/texture.c src/headers/texture.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/texture.o src/texture.c

triangle.o : src/triangle.c src/headers/triangle.h \
src/headers/display.h src/headers/swap.h src/headers/texture.h \
src/headers/upng.h src/headers/vector.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/triangle.o src/triangle.c

upng.o : src/upng.c src/headers/upng.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/upng.o src/upng.c

vector.o : src/vector.c src/headers/vector.h
	$(CC) $(CFLAGS) $(INC_PATH) -c -o obj/vector.o src/vector.c


run:
	$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ_FILES)