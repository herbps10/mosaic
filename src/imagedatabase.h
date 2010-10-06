class ImageDatabase {
	public:
	ImageDatabase();
	string rgbToHex(int r, int g, int b);
	Image closestImage(int color);
	string digitToHex(int n);
	void roundColor(int& r, int& g, int& b);
	string colorPath(string hex, int variant);
};
