#    Dylan Campbell
#    campbell.dyl@gmail.com
#    3D Graphics Renderer in C

CC = gcc
CFLAGS = -std=c99 -Wall -g -O0
INC_PATH = -Isrc/headers/
LIBS = -lSDL2 -lm

TARGET = bin/renderer
SRC_FILES = src/*.c
OBJ_FILES = obj/array.o obj/camera.o obj/clipping.o obj/display.o obj/light.o \
obj/main.o obj/matrix.o obj/mesh.o obj/swap.o obj/texture.o obj/triangle.o \
obj/upng.o obj/vector.o

#-------------------------------------------------------------------------------
# make                  makes executable
# make build            makes all (missing/old) obj files and executable
# make run              executes binary
# make clean            removes all object files and executable
# make check            checks executable for memory errors via valgrind
#-------------------------------------------------------------------------------


# make -------------------------------------------------------------------------
renderer :
	$(CC) $(CFLAGS) $(INC_PATH) $(SRC_FILES) $(LIBS) -o $(TARGET)


# make build -------------------------------------------------------------------
build : $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LIBS) -o $(TARGET)

obj/array.o : src/array.c src/headers/array.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/array.c -o obj/array.o

obj/camera.o : src/camera.c src/headers/camera.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/camera.c -o obj/camera.o

obj/clipping.o : src/clipping.c src/headers/clipping.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/clipping.c -o obj/clipping.o

obj/display.o : src/display.c src/headers/display.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/display.c -o obj/display.o

obj/light.o : src/light.c src/headers/light.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/light.c -o obj/light.o

obj/main.o : src/main.c
	$(CC) $(CFLAGS) $(INC_PATH) -c src/main.c -o obj/main.o

obj/matrix.o : src/matrix.c src/headers/matrix.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/matrix.c -o obj/matrix.o

obj/mesh.o : src/mesh.c src/headers/mesh.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/mesh.c -o obj/mesh.o

obj/swap.o : src/swap.c src/headers/swap.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/swap.c -o obj/swap.o

obj/texture.o : src/texture.c src/headers/texture.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/texture.c -o obj/texture.o

obj/triangle.o : src/triangle.c src/headers/triangle.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/triangle.c -o obj/triangle.o

obj/upng.o : src/upng.c src/headers/upng.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/upng.c -o obj/upng.o

obj/vector.o : src/vector.c src/headers/vector.h
	$(CC) $(CFLAGS) $(INC_PATH) -c src/vector.c -o obj/vector.o


# make run ---------------------------------------------------------------------
run :
	$(TARGET)

# make clean -------------------------------------------------------------------
clean :
	rm -f $(TARGET) $(OBJ_FILES)

# make check -------------------------------------------------------------------
check :
	valgrind --leak-check=full $(TARGET)
