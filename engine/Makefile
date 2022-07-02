CC := cc
CFLAGS := -std=gnu17
IFLAGS := -Iinclude -Isrc -Ilibs/glad/include -Ilibs/glfw/include -Ilibs/stb
LFLAGS :=
DFLAGS :=

debug test: CFLAGS += -ggdb -Wall -Wextra
release: CFLAGS += -O3

SRC := $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c) libs/glad/src/glad.c
OBJ = $(SRC:%.c=%.o)
GLFW :=

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $^ -o $@ $(IFLAGS)

build_glfw:
	cd libs/glfw ; make

colossus: GLFW += $(wildcard libs/glfw/src/*.o)
colossus: $(OBJ) build_glfw
	mkdir -p bin
	ar rcs bin/libcolossus.a $(OBJ) $(GLFW)

debug release: colossus

.PHONY: clean

clean:
	rm $(OBJ) bin/libcolossus.a

test: debug
	$(CC) $(CFLAGS) -Itests -Iinclude $(wildcard tests/*.c) -o bin/test -Lbin -lcolossus -lm