class ImageCache {
	private:
	static ImageCache instance;
	map<string, Image> images;

	public:
	void add(string hex, int variant, Image image);
	bool get(string hex, int variant, Image& image);
	static ImageCache &getInstance();
};
