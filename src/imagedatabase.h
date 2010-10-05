// Accesses the database of pictures over the network

class ImageDatabase {
	public:
	ImageDatabase();
	//Image closestImage(int color);
	void connect(unsigned int address);
	void getImageSize(int &x, int &y);
	string rgbToHex(int r, int g, int b);
	Image closestImage(int color);
	string digitToHex(int n);
	void roundColor(int& r, int& g, int& b);
	string colorPath(string hex, int variant);
};
