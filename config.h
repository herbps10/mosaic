const int FPS = 20; // Frames Per Second

// The size of the box to sample from the source image
const int SAMPLE_X = 100;
const int SAMPLE_Y = 100;

// Whether to resize the source images. Faster if set to false.
const bool RESIZE_IMAGES = false;

// The size to resize the library images to
const int RESIZE_X = 75;
const int RESIZE_Y = 75;

// This won't have any effect if FULLSCREEN is set to true
int SCREEN_X = 500;
int SCREEN_Y = 500;

const bool FULLSCREEN = false;

// Whether to add the hex value to each image so you can see which color it is
const bool COLOR_DEBUG = false;
