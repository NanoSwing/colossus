CC := cc
CFLAGS := -std=gnu17
IFLAGS := -I../engine/include -Isrc
LFLAGS := -L../engine/bin -lcolossus
DFLAGS :=

# OS detection
ifeq ($(OS), Windows_NT)
	LFLAGS += -L../engine/libs/glfw/lib -lglfw3
else
	LFLAGS += -lglfw
endif

debug: CFLAGS += -ggdb -Wall -Wextra
release: CFLAGS += -O3

SRC := $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c)
OBJ = $(SRC:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(IFLAGS)

testbed: $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) -o bin/testbed $(LFLAGS)

debug release: testbed

.PHONY: clean

clean:
	rm -f $(OBJ) bin/testbed
