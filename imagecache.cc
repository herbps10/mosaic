#include "imagecache.h"

ImageCache ImageCache::instance;

ImageCache &ImageCache::getInstance() {
	return instance;
}

/*
 * Add an image to the cache
 *
 * string hex - the average color of the image in RGB hex format
 * int variant - the version of the color, to differentiate multiple images with the same average color
 * Image image - the image to add to the cache
 */
void ImageCache::add(string hex, int variant, Image image) {
	std::stringstream out;
	out << variant;
	images.insert(pair<string, Image>(hex + "-" + out.str(), image));
}

/*
 * Retrieve an image from the cache
 */
bool ImageCache::get(string hex, int variant, Image& image) {
	std::stringstream out;
	out << variant;

	map<string, Image>::iterator iter = images.find(hex + "-" + out.str());

	if(iter == images.end()) {
		return false;
	}
	else {
		Image i = images[hex + "-" + out.str()];
		
		if(i.height() != RESIZE_Y || i.width() != RESIZE_X) {
			// This means that the images in the cache are not the right size for the source image. Clear the cache so that the images will be re-loaded and re-sized.
			clear();
			return false;
		}
		else {
			image = i;
			return true;
		}
	}
}

/*
 * Clear the cache
 */
void ImageCache::clear() {
	images.clear();
}
