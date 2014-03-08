pong: src/main.c src/main.h
	gcc `sdl-config --cflags --libs` -lm -lSDL_image -lSDL_ttf -lSDL_gfx -o pong src/main.c
