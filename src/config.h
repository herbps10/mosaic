const int FPS = 20; // Frames Per Second

// The size of the box to sample from the source image
const int SAMPLE_X = 20;
const int SAMPLE_Y = 20;

// Whether to resize the source images. Faster if set to false.
const bool RESIZE_IMAGES = true;

// The size to resize the library images to
int RESIZE_X = 10;
int RESIZE_Y = 10;

// This won't have any effect if FULLSCREEN is set to true
int SCREEN_X = 1280; 
int SCREEN_Y = 1024; 

bool FULLSCREEN = true;

// Whether to add the hex value to each image so you can see which color it is
bool COLOR_DEBUG = false;

// Whether to draw each image individually or wait until the calculations are completely done and draw it all at once
bool DRAW_EACH = false;

const int WALL_ROWS = 2; // the number of rows of screens in the wall
const int WALL_COLUMNS = 2; // The number of columns in the wall
