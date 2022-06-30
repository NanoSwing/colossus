CC := cc
CFLAGS := -std=c17 -ggdb -Wall
IFLAGS := -Iinclude -Isrc

DFLAGS := -D_GLFW_USE_OPENGL
LFLAGS :=

SRC := context.c init.c input.c monitor.c null_init.c null_joystick.c null_monitor.c null_window.c platform.c vulkan.c window.c egl_context.c osmesa_context.c

#
# OS Detection
#

# Windows
ifeq ($(OS), Windows_NT)
	DFLAGS += -D_WIN32 -D_GLFW_WIN32 -D_GLFW_WGL
	SRC += win32_init.c win32_joystick.c win32_module.c win32_monitor.c win32_thread.c win32_time.c win32_window.c wgl_context.c
	LFLAGS += -lgdi32
# Linux
else
	DFLAGS += -D_GLFW_X11 -D_GLFW_GLX -D_GLFW_HAS_GLXGETPROCADDRESS -D_POSIX_C_SOURCE=199309L
	SRC += glx_context.c linux_joystick.c x11_init.c x11_monitor.c x11_window.c xkb_unicode.c posix_thread.c posix_time.c posix_module.c posix_poll.c
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
