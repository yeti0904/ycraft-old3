#include "image.hh"
#include "util.hh"

void ImageComponents::Init() {
	int flags = IMG_INIT_PNG;
	if (IMG_Init(flags) != flags) {
		Util::Error("Failed to initialise SDL_image");
	}
}

void ImageComponents::Free() {
	IMG_Quit();
}
