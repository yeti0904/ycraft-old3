#include "image.hh"

void ImageComponents::Init() {
	int flags = IMG_INIT_PNG;
	if (IMG_Init(flags) != flags) {
		fprintf(stderr, "[ERROR] Failed to initialise SDL_image");
		exit(EXIT_FAILURE);
	}
}

void ImageComponents::Free() {
	IMG_Quit();
}
