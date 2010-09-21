#include "sdl.h"

SDL SDL::instance;

SDL &SDL::getInstance() {
	return instance;
}

/*
 * Initialize SDL and the main surface
 */
void SDL::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	if(FULLSCREEN == true) {
		screen = SDL_SetVideoMode(0, 0, 32, SDL_SWSURFACE | SDL_FULLSCREEN);

		const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();

		SCREEN_X = videoInfo->current_w;
		SCREEN_Y = videoInfo->current_h;
	}
	else {
		//screen = SDL_SetVideoMode(SOURCE_X * (RESIZE_X / SAMPLE_X), SOURCE_Y * (RESIZE_Y / SAMPLE_Y), 32, SDL_SWSURFACE);
		screen = SDL_SetVideoMode(SCREEN_X, SCREEN_Y, 32, SDL_SWSURFACE);
	}
	SDL_Flip(screen);
}

/*
 * Draw a pixel of a given RGB color on the main SDL screen
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
	*p = color;
}
