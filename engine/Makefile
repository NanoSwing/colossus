CC := cc
CFLAGS := -std=gnu17
IFLAGS := -Iinclude -Isrc -Ilibs/glad/include -Ilibs/glfw/include
LFLAGS :=
DFLAGS :=

# OS detection
ifeq ($(OS), Windows_NT)
	LFLAGS += -L../engine/libs/glfw/lib -lglfw3
else
	LFLAGS += -lglfw
endif

debug test: CFLAGS += -ggdb -Wall -Wextra
release: CFLAGS += -O3

SRC := $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c) libs/glad/src/glad.c
OBJ = $(SRC:%.c=%.o)
GLFW := $(wildcard libs/glfw/src/*.o)

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $^ -o $@ $(IFLAGS)

colossus: $(OBJ)
	cd libs/glfw ; make
	mkdir -p bin
	ar rcs bin/libcolossus.a $(OBJ) $(GLFW)

debug release: colossus

.PHONY: clean

clean:
	rm $(OBJ) bin/libcolossus.a

test: debug
	$(CC) $(CFLAGS) -Itests -Iinclude $(wildcard tests/*.c) -o bin/test -Lbin -lcolossus