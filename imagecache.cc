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
		image = images[hex + "-" + out.str()];
		return true;
	}
}
