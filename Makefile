CC 	= mpic++

mosaic: src/main.cpp
	$(CC) -o mosaic -lSDL -lSDL_image -lX11 src/main.cpp
