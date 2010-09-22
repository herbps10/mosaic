#include "image.h"

Image::Image() {
	
}

void Image::loadCImg(cimg_library::CImg<int> img) {
	image = img;
}

/*
 * Finds the average color of a subset of the image
 */
int Image::average(int x, int y, int w, int h) {
	int r = 0, b = 0, g = 0;
	int size = w * h;

	for(int i = x; i < x + w; i++) {
		for(int n = y; n < y + h; n++) {
			r += image.atXY(i, n, 0);
			g += image.atXY(i, n, 1);
			b += image.atXY(i, n, 2);
		}
	}

	r /= size;
	g /= size;
	b /= size;

	return SDL_MapRGB(SDL::getInstance().screen->format, r, g, b);
}

/*
 * Find the color average of the whole image
 */
int Image::average() {
	average(0, 0, image.width(), image.height());
}

/*
 * Draws the image to the SDL screen at the given coordinates
 *
 */
void Image::drawImage(int xOffset, int yOffset) {
	// This works by looping through every pixel of the cimg and drawing it on the SDL surface
	cimg_forXY(image, x, y) {
		// Make sure we don't try to write outside the window
		if(x + xOffset < SCREEN_X && y + yOffset < SCREEN_Y) {
			SDL::getInstance().drawPixel(x + xOffset, y + yOffset, image.atXY(x, y, 0), image.atXY(x, y, 1), image.atXY(x, y, 2));
		}
	}
}

/*
 * Draws the image to the SDL screen at the origin
 */
void Image::drawImage() {
	drawImage(0, 0);
}

/*
 * Resize the image to the correct size as given in the config.h file
 */
void Image::resizeToConfig() {
	image.resize(RESIZE_X, RESIZE_Y);
}

int Image::width() {
	return image.width();
}

int Image::height() {
	return image.height();
}
