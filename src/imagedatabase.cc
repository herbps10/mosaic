#include "imagedatabase.h"

ImageDatabase::ImageDatabase() {

}

/*
 * Finds the image with the closest color average and returns it
 *
 * int color - an SDL mapped color value to search for
 */
Image ImageDatabase::closestImage(int color) {
	// Extract the RGB values from the 
	int r, g, b;
	SDL_GetRGB(color, SDL::getInstance().screen->format, (Uint8 *)&r, (Uint8 *)&g, (Uint8 *)&b);

	if(rand() % 3 == 0) {
		r += 16;
		b += 16;
		g += 16;
	}

	roundColor(r, g, b);

	string hex = rgbToHex(r, g, b);

	int variant = 0;

	if(fileExists(colorPath(hex, 1))) {
		if(rand() % 3 == 0) {
			variant = 1;
		}
	}

	Image cached;
	if(ImageCache::getInstance().get(hex, variant, cached)) {
		return cached;
	}
	else {
		string file = colorPath(hex, variant);
		
		if(fileExists(colorPath(hex, variant))) file = colorPath(hex, variant);

		cimg_library::CImg<int> img(file.c_str());

		if(COLOR_DEBUG == true) {
			unsigned int black[] = {0, 0, 0};
			img.draw_text(20, 20, hex.c_str(), black);
		}
		
		Image* image = new Image();

		image->loadCImg(img);

		if(RESIZE_IMAGES == true) {
			image->resizeToConfig();
		}

		ImageCache::getInstance().add(hex, variant, *image);

		return *image;
	}
}

string ImageDatabase::colorPath(string hex, int variant) {
	std::stringstream out;
	out << variant;
	return "scraper/images/" + hex + "-" + out.str() + ".jpg";
}

/*
 * Connects to the master image database
 *
 * unsigned int address - the ip address of the server
 */
void ImageDatabase::connect(unsigned int address) {

}

void ImageDatabase::roundColor(int& r, int& g, int& b) {
	// Round each number to the closest multiple of 16.
	r = (r + 8) - ((r + 8) % 16);
	g = (g + 8) - ((g + 8) % 16);
	b = (b + 8) - ((b + 8) % 16);

	if(r >= 256) r = 240;
	if(g >= 256) g = 240;
	if(b >= 256) b = 240;
}

string ImageDatabase::rgbToHex(int r, int g, int b) {
	string result = "";
	int colors [] = {r, g, b};		

	for(int i = 0; i < 3; i++) {
		int divs = colors[i] / 16;
		int rem = colors[i] % 16;

		result += digitToHex(divs) + digitToHex(rem);
	}

	return result;
}

string ImageDatabase::digitToHex(int n) {
	string alphabet [] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"};
	
	return alphabet[n];
}

/*
 * Get the size of the images in the database
 */
void ImageDatabase::getImageSize(int &x, int &y) {

}
