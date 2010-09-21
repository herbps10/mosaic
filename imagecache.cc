#include "imagecache.h"

ImageCache ImageCache::instance;

ImageCache &ImageCache::getInstance() {
	return instance;
}

void ImageCache::add(string hex, int variant, Image image) {
	std::stringstream out;
	out << variant;
	images.insert(pair<string, Image>(hex + "-" + out.str(), image));
}

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
