// Provides global access to SDL and the main SDL surface

class SDL {
	private:
	static SDL instance;

	public:
	SDL_Surface* screen;
	static SDL &getInstance();
	void init();
	void drawPixel(int x, int y, int r, int g, int b);
	void drawPixel(int x, int y, int color);
};
