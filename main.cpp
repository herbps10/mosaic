#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include <cstdlib>
#include <string>

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "CImg.h"

using namespace cimg_library;
using namespace std;

#include "config.h"

#include "functions.cc"
#include "sdl.cc"
#include "timer.cc"
#include "image.cc"
#include "imagecache.cc"
#include "imagedatabase.cc"
#include "mosaic.cc"

#include "main.h"

void loop() {
	int frame = 0;
	bool quit = false;
	//Timer fps;
	SDL_Event event;
	while(quit == false) {
		//fps.start();

		while(SDL_PollEvent(&event)) {
			// This only responds to Ctrl-C as far as I can tell
			if(event.type == SDL_QUIT) {
				quit = true;
			}
		}

		/*
		frame++;

		// Cap the frame rate if necessary
		if(fps.get_ticks() < 1000 / FPS) {
			SDL_Delay(1000 / FPS - fps.get_ticks());
		}

		SDL_Flip(SDL::getInstance().screen);
		*/
	}
}

int main(int argc, char* args[]) {
	SDL::getInstance().init();

	ImageDatabase* database = new ImageDatabase();

	mosaic("flower.jpg", database);

	SDL_Delay(1000);

	mosaic("blobs.jpg", database);

	SDL_Delay(1000);

	mosaic("flower.jpg", database);

	// Loop for events
	loop();

	SDL_Quit();

	return 0;
}

void mosaic(string file, ImageDatabase* database) {
	//Clear the screen
	SDL_FillRect(SDL::getInstance().screen, NULL, SDL_MapRGB(SDL::getInstance().screen->format, 0, 0, 0));

	// Load the source image
	CImg<int> sourceImage(file.c_str());
	
	int SOURCE_X = sourceImage.width();
	int SOURCE_Y = sourceImage.height();

	Image* source = new Image();
	source->loadCImg(sourceImage);

	// Calculate how many samples you have to take
	int numX, numY;
	numX = SOURCE_X / SAMPLE_X;
	numY = SOURCE_Y / SAMPLE_Y;

	// Figure out what size we need to resize the library images to in order to fit in the entire width of the source image
	RESIZE_X = SCREEN_X / numX;
	RESIZE_Y = RESIZE_X; // Keep the resized image square

	// Explanation of parameters to Mosaic constructor
	// numX - number of images across
	// numY - number of images down
	// RESIZE_X - width of final replacement image
	// RESIZE_Y height of final replacement image
	Mosaic* m = new Mosaic(numX, numY, RESIZE_X, RESIZE_Y);

	Image replacement;
	int averageColor;
	for(int x = 0; x < numX; x++) {
		for(int y = 0; y < numY; y++) {
			// Average the sample segment of the source image.
			// and find the closest match in the image database
			averageColor = source->average(x * SAMPLE_X, y * SAMPLE_Y, RESIZE_X, RESIZE_Y);
			replacement = database->closestImage(averageColor);

			m->addImage(x, y, replacement);
		}
	}

	if(DRAW_EACH == false) {
		m->draw();
	}
	
	delete m;
}


