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

	if(DRAW_EACH == true) {
		image.drawImage(column * imageWidth, row * imageHeight);
		SDL_Flip(SDL::getInstance().screen);
	}
}

/*
 * Draw the mosaic to the screen
 */
void Mosaic::draw() {
	for(int r = 0; r < numRows; r++) {
		for(int c = 0; c < numColumns; c++) {
			images[r][c].drawImage(c * imageWidth, r * imageHeight);
		}
	}

	SDL_Flip(SDL::getInstance().screen);
}
