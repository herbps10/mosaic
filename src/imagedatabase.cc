#include "imagedatabase.h"

ImageDatabase::ImageDatabase() {

}

/*
 * Finds the image with the closest color average and returns it
 *
 * int color - an SDL mapped color value to search for
 */
Image ImageDatabase::closestImage(int color) {
	
	// Extract the RGB values from the color parameter
	SDL_Color extractedColor;
	int r, g, b;
	SDL_GetRGB(color, SDL::getInstance().screen->format, &extractedColor.r, &extractedColor.g, &extractedColor.b);
	r = (int)extractedColor.r;
	g = (int)extractedColor.g;
	b = (int)extractedColor.b;

	/* Summary: This randomizes what image is returned.
	   Explanation: Sometimes in the source image there are several samples that have very similar color averages. Since we don't have very much variety in the image library, that means that the same replacement image will be used multiple times in a small area. While this isn't necessarily a bad thing, it looks somewhat ugly. To avoid this, we can try to randomize what image is returned. The following code will randomly change the color of a pixel one half of the time. This means that instead of choosing the "correct" replacement image for that sample, it will choose one that is of a slightly different color. */
	if(rand() % 3 == 0) {
		r += 16;
		b += 16;
		g += 16;
	}

	//The image library is somewhat limited, and there isn't an image for every possible color. As such, we need to round the color to the closest value that we do have.  
	roundColor(r, g, b);

	// All of the images in the library are stored by hex value rather than RGB. As such, in order to load the file we need to convert our RGB value into hex.
	string hex = rgbToHex(r, g, b);

	/*
	This is another attempt to randomize the end result.
	In the image library, there are some duplicate colors. For example, there might be two images that both have a blue color average. However, only some of colors in the library have two images with the same color. As such, we need to double check that the file exists before we can try to use it. If it does exist, then one of the images is chosen randomly.
	*/
	int variant = 0;

	if(fileExists(colorPath(hex, 1))) {
		if(rand() % 3 == 0) {
			variant = 1;
		}
	}


	/*
	Every time an image is loaded from disk, it is stored in memory for faster retrieval. 
	Here we check to see if the image is in the cache. If so, we just return that image. If not, we load the image from disk, process it, insert it into the cache, and return the image.
	*/
	Image cached;
	if(ImageCache::getInstance().get(hex, variant, cached)) {
		return cached;
	}
	else {
		string file = colorPath(hex, variant);
		cimg_library::CImg<int> img(file.c_str());

		Image* image = new Image();
		image->loadCImg(img);

		if(RESIZE_IMAGES == true) {
			image->resizeToConfig(); // This function resizes the replacement images to the size specified in config.h
		}
		
		/*
		Color debugging will write the average color of the image onto the image
		*/
		if(COLOR_DEBUG == true) {
			image->addText(hex);
		}

		// Add the image to the cache
		ImageCache::getInstance().add(hex, variant, *image);

		return *image;
	}
}

string ImageDatabase::colorPath(string hex, int variant) {
	std::stringstream out;
	out << variant;
	return "images/" + hex + "-" + out.str() + ".jpg";
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

/**
 * Converts a single digit integer (0-15) to its hex equivalent.
 */
string ImageDatabase::digitToHex(int n) {
	string alphabet [] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"};
	
	return alphabet[n];
}
