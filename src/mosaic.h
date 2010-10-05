using namespace std;

class Mosaic {
	private:
	vector<vector<Image> > images;

	int numImages;
	int numColumns, numRows;
	int imageHeight, imageWidth;

	public:

	Mosaic(int columns, int rows, int iHeight, int iWidth);
	~Mosaic();
	void addImage(int column, int row, Image image);
	void draw();
};
