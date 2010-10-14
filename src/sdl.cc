#include "sdl.h"

SDL SDL::instance;

SDL &SDL::getInstance() {
	return instance;
}

/*
 * Initialize SDL and the main surface. The surface will either be full screen or a specific size depending on the settings in the configuration file.
 */
void SDL::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	if(FULLSCREEN == true) {
		screen = SDL_SetVideoMode(0, 0, 32, SDL_ANYFORMAT | SDL_HWSURFACE | SDL_FULLSCREEN);

		// Retrieve the size of the screen
		const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
		SCREEN_X = videoInfo->current_w;
		SCREEN_Y = videoInfo->current_h;
	}
	else {
		screen = SDL_SetVideoMode(SCREEN_X, SCREEN_Y, 32, SDL_ANYFORMAT | SDL_HWSURFACE);
	}

	if(screen == NULL) {
		cout << "Error initializing the screen\n";
	}

	SDL_Flip(screen);
}

/*
 * Draw a pixel of a given RGB color on the main SDL screen
 * This function maps the rgb values to an SDL formatted integer and passes it to the other version of the drawPixel function.
 */
void SDL::drawPixel(int x, int y, int r, int g, int b) {
	drawPixel(x, y, SDL_MapRGB(SDL::getInstance().screen->format, r, g, b));
}

/*
 * Draw a colormapped pixel to the main SDL screen
 *
 * int color - SDL colormapped color
 */
void SDL::drawPixel(int x, int y, int color) {
	int *p = (int *)SDL::getInstance().screen->pixels + y * SDL::getInstance().screen->pitch/4 + x;
	*p = color; // If you get a segmentation fault here, it is probably because you are trying to write to out of bound coordinates.
}
