CC := cc
CFLAGS := -std=c17 -ggdb -Wall
IFLAGS := -Iinclude -Isrc

DFLAGS := -D_GLFW_USE_OPENGL -D_POSIX_C_SOURCE=199309L
LFLAGS :=

SRC := context.c init.c input.c monitor.c null_init.c null_joystick.c null_monitor.c null_window.c platform.c vulkan.c window.c posix_module.c posix_poll.c posix_thread.c posix_time.c egl_context.c osmesa_context.c

#
# OS Detection
#

# Windows
ifeq ($(OS), Windows_NT)
	DFLAGS += -D_GLFW_WIN32 -D_GLFW_WGL
# Linux
else
	DFLAGS += -D_GLFW_X11 -D_GLFW_GLX -D_GLFW_HAS_GLXGETPROCADDRESS
	SRC += glx_context.c linux_joystick.c x11_init.c x11_monitor.c x11_window.c xkb_unicode.c
	LFLAGS += -lm
endif

SRC := $(addprefix src/,$(SRC))
OBJ := $(SRC:%.c=%.o)


%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(IFLAGS) $(DFLAGS)

all: $(OBJ)

.PHONY: clean test

clean:
	rm -f $(OBJ)

test: $(OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) test/test.c $(OBJ) -o test/test $(LFLAGS)
