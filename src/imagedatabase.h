class ImageDatabase {
	public:
	ImageDatabase();
	static string rgbToHex(int r, int g, int b);
	Image closestImage(int color);
	static string digitToHex(int n);
	static void roundColor(int& r, int& g, int& b);
	string colorPath(string hex, int variant);
};
