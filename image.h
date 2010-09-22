using namespace std;

class Image {
	private:
	cimg_library::CImg<int> image;

	public:
	Image();
	void loadCImg(cimg_library::CImg<int> img);
	int average();
	int average(int x, int y, int w, int h);
	void drawImage();
	void drawImage(int xOffset, int yOffset);
	void resizeToConfig();
	int width();
	int height();
};
