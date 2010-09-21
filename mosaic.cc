#include "mosaic.h"

Mosaic::Mosaic(int columns, int rows, int iHeight, int iWidth) {
	numColumns = columns;
	numRows = rows;

	imageHeight = iHeight;
	imageWidth = iWidth;

	numImages = numColumns * numRows;

	// The images array is used to store the images for the mosaic
	// Resize the array to the correct size based on the number of images that will be in the mosaic
	images.resize(numRows);
	for(int i = 0; i < numRows; i++) {
		images[i].resize(numColumns);
	}
}

Mosaic::~Mosaic() {
}

/*
 * Inserts an image into the mosaic
 * 
 * int column - the column to insert the image into
 * int row - the row the image will go in
 */
void Mosaic::addImage(int column, int row, Image image) {
	images[row][column] = image;
}

/*
 * Draw the mosaic to the screen
 */
void Mosaic::draw() {
	for(int r = 0; r < numRows; r++) {
		// Make sure we don't overrun the screen vertically. r * imageHeight gives us the upper hand coordinate of the image -- add imageHeight so we can get the lower coordinate
		if((r * imageHeight + imageHeight) < SCREEN_Y) {
			for(int c = 0; c < numColumns; c++) {
				// Make sure we don't run off the right edge of the screen. c * imageWidth gives us the left side coordinate, add imageWidth to get the right side
				if((c * imageWidth + imageWidth) < SCREEN_X) {
					images[r][c].drawImage(c * imageWidth, r * imageHeight);
				}
			}
		}
	}

	SDL_Flip(SDL::getInstance().screen);
}
