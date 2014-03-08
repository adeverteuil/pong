CC = gcc
CFLAGS ?= -g

OBJS = window.o ball.o game.o

all: pong

pong: src/main.c $(OBJS)
	$(CC) $(CFLAGS) -o pong \
	`sdl-config --cflags --libs` \
	-lm -lSDL_gfx build/*.o src/main.c

window.o:
	$(CC) -c $(CFLAGS) -o build/window.o \
	`sdl-config --cflags --libs` src/window.c

ball.o:
	$(CC) -c $(CFLAGS) -o build/ball.o \
	`sdl-config --cflags --libs` -lm src/ball.c

game.o:
	$(CC) -c $(CFLAGS) -o build/game.o \
	`sdl-config --cflags --libs` src/game.c
