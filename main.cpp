#include "mpi.h"

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
	bool quit = false;
	SDL_Event event;


	while(quit == false) {
		while(SDL_PollEvent(&event)) {
			// This only responds to Ctrl-C as far as I can tell
			if(event.type == SDL_QUIT) {
				quit = true;
			}
			else if(event.type == SDL_KEYDOWN) {
				char keyName = event.key.keysym.sym;
				if(keyName == 'q' || keyName == 'Q') {
					quit = true;
				}
			}
		}
	}
}

int main(int argc, char* args[]) {
	SDL::getInstance().init();

	string file = "/opt/mosaic/sources/flower.jpg";
	ImageDatabase* database = new ImageDatabase();

	MPI_Init(&argc, &args);

	int numNodes, node;
	
	MPI_Comm_size(MPI_COMM_WORLD, &numNodes);
	MPI_Comm_rank(MPI_COMM_WORLD, &node);

	mosaic(file, node, numNodes, database);

	// Loop for events
	//loop();
	SDL_Delay(5000);

	MPI_Finalize();
	SDL_Quit();

	return 0;
}

void mosaic(string file, int node, int numNodes, ImageDatabase* database) {
	//Clear the screen
	SDL_FillRect(SDL::getInstance().screen, NULL, SDL_MapRGB(SDL::getInstance().screen->format, 0, 0, 0));

	// Load the source image
	CImg<int> sourceImage(file.c_str());

	Image* source = new Image();
	source->loadCImg(sourceImage);

	// Crop out the part of the image that this node needs to draw
	int startX, startY, cropWidth, cropHeight, wallRow, wallColumn;

	//Figure out where we are on the video wall
	wallRow = node % 4; // This is 0 indexed, so values will range from 0-3
	wallColumn = node / 4; // Again, 0 indexed

	printf("%i %i\n", wallRow, wallColumn);

	cropWidth = source->width() / 4;
	cropHeight = source->height() / 4;

	startX = wallColumn * cropWidth;
	startY = wallRow * cropHeight;

	// Calculate how many samples you have to take
	int numX, numY;
	numX = cropWidth / SAMPLE_X;
	numY = cropHeight / SAMPLE_Y;

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
