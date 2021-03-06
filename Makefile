# Makefile for pong program.

# http://wiki.libsdl.org/FAQLinux#How_do_I_add_SDL_to_my_project.3F
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs)

CC = gcc
CFLAGS = $(SDL_CFLAGS) -g
LDFLAGS = $(SDL_LDFLAGS) -lm -lSDL_gfx -lSDL_ttf

# End of configuration.

.PHONY: all
all: pong

OBJS = pong.o ai.o window.o ball.o game.o paddle.o physics.o text.o options.o renderer.o

pong: $(OBJS)

ball.o: ball.c math.h ball.h
game.o: game.c math.h game.h options.h
paddle.o: paddle.h
pong.o: game.h pong.h window.h
window.o: window.h
physics.o: physics.h
text.o: text.h
options.o: options.h
renderer.o: renderer.h
ai.o: ai.h

.PHONY: clean
clean:
	-rm *.o pong
