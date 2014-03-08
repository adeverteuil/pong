CC = gcc
CFLAGS ?= -g

OBJS = build/window.o

all: pong

pong: $(OBJS)
	$(CC) $(CFLAGS) -o pong \
	`sdl-config --cflags --libs` \
	-lm -lSDL_gfx build/*.o src/main.c

window.o:
	$(CC) -c $(CFLAGS) -o build/window.o \
	`sdl-config --cflags --libs` src/window.c
