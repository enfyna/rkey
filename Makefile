CC=clang

FLAGS=-pedantic -Wall -Wextra 
INC_RAYLIB=-I./raylib-5.0_linux_amd64/include/ -L./raylib-5.0_linux_amd64/lib/ -lraylib

default: build/rkey

build/rkey: src/main.c
	$(CC) $(FLAGS) -o build/rkey src/main.c $(INC_RAYLIB) -lm -I./include/
