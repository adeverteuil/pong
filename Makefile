pong: main.c
	gcc `sdl-config --cflags --libs` -lm -lSDL_image -lSDL_ttf -lSDL_gfx -o pong main.c
