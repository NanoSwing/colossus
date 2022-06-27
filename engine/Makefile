CC := cc
CFLAGS := -std=gnu17
IFLAGS := -Ilibs/glad/include -Iinclude -Isrc
LFLAGS := -lglfw
DFLAGS :=

debug test: CFLAGS += -ggdb -Wall -Wextra
release: CFLAGS += -O3

SRC := $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c) libs/glad/src/glad.c
OBJ = $(SRC:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $^ -o $@ $(IFLAGS)

chameleon: $(OBJ)
	mkdir -p bin
	ar rcs bin/libchameleon.a $(OBJ)

debug release: chameleon

.PHONY: clean

clean:
	rm $(OBJ) bin/libchameleon.a

test: debug
	$(CC) $(CFLAGS) -Itests -Iinclude $(wildcard tests/*.c) -o bin/test -Lbin -lchameleon
