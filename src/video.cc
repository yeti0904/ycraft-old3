#include "video.hh"
#include "constants.hh"
#include "util.hh"

void VideoComponents::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "[ERROR] Failed to initialise SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow(
		(std::string(APP_NAME) + " " + APP_VERSION).c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480,
		SDL_WINDOW_RESIZABLE
	);

	if (window == nullptr) {
		fprintf(stderr, "[ERROR] Failed to create window\n");
		exit(EXIT_FAILURE);
	}
	Util::Log("Created window");
	
	renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (renderer == nullptr) {
		fprintf(stderr, "[ERROR] Failed to create renderer\n");
		exit(EXIT_FAILURE);
	}
	Util::Log("Created renderer");

	SDL_RenderSetLogicalSize(renderer, APP_SCREEN_SIZE_W, APP_SCREEN_SIZE_H);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void VideoComponents::Free() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
