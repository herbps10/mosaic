#include "mosaic.h"

Mosaic::Mosaic(int columns, int rows, int iHeight, int iWidth) {
	numColumns = columns;
	numRows = rows;

	imageHeight = iHeight;
	imageWidth = iWidth;

	numImages = numColumns * numRows;

	// Resize the 2d image array
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

	images[row][column].drawImage(column * imageWidth, row * imageHeight);
}

/*
 * Draw the mosaic to the screen
 */
void Mosaic::draw() {
	for(int r = 0; r < numRows; r++) {
		if((r * imageHeight) < SCREEN_Y) {
			for(int c = 0; c < numColumns; c++) {
				if((c * imageWidth) < SCREEN_X) {
					images[r][c].drawImage(c * imageWidth, r * imageHeight);
				}
			}
		}
	}

	SDL_Flip(SDL::getInstance().screen);
}
