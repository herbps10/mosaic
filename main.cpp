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

#include "main.h"

#include "sdl.cc"
#include "timer.cc"
#include "image.cc"
#include "imagecache.cc"
#include "imagedatabase.cc"
#include "mosaic.cc"

void loop() {
	int frame = 0;
	bool quit = false;
	//Timer fps;
	SDL_Event event;
	while(quit == false) {
		//fps.start();

		while(SDL_PollEvent(&event)) {
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

	CImg<int> sourceImage("flower.jpg");

	Image* source = new Image();
	source->loadCImg(sourceImage);

	int numX, numY;
	numX = SOURCE_X / SAMPLE_X;
	numY = SOURCE_Y / SAMPLE_Y;

	Mosaic* m = new Mosaic(numX, numY, RESIZE_X, RESIZE_Y);

	Image replacement;
	int averageColor;
	for(int x = 0; x < numX; x++) {
		for(int y = 0; y < numY; y++) {
			averageColor = source->average(x * SAMPLE_X, y * SAMPLE_Y, RESIZE_X, RESIZE_Y);
			replacement = database->closestImage(averageColor);

			m->addImage(x, y, replacement);
		}
	}

	m->draw();

	loop();

	SDL_Quit();

	return 0;
}

bool fileExists(string path) {
	struct stat fileInfo;
	int intStat;

	intStat = stat(path.c_str(), &fileInfo);

	if(intStat == 0) {
		return true;
	}
	else {
		return false;
	}
}
