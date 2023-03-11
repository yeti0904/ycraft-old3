#include "video.hh"
#include "constants.hh"
#include "util.hh"

void VideoComponents::Init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		Util::Error("Failed to initialise SDL: %s\n", SDL_GetError());
	}

	if(SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0) {
		Util::Error("Failed to initialise SDL Controller API: %s\n", SDL_GetError());
	}

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

	#if defined(PLATFORM_VITA)
		// VITA: The psvita does not generate mouse events
		SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
	#endif

	int w = APP_SCREEN_SIZE_W;
	int h = APP_SCREEN_SIZE_H;

	#if defined(PLATFORM_VITA)
		w = 960;
		h = 554;
	#endif

	window = SDL_CreateWindow(
		(std::string(APP_NAME) + " " + APP_VERSION).c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		w, h,
		SDL_WINDOW_RESIZABLE
	);

	if (window == nullptr) {
		Util::Error("Failed to create window: %s", SDL_GetError());
	}
	Util::Log("Created window");

	renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (renderer == nullptr) {
		Util::Error("Failed to create renderer: %s", SDL_GetError());
	}
	Util::Log("Created renderer");

	SDL_RenderSetLogicalSize(renderer, APP_SCREEN_SIZE_W, APP_SCREEN_SIZE_H);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void VideoComponents::Free() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void VideoComponents::DrawTriangle(
	FVec2 point1, FVec2 point2, FVec2 point3, SDL_Color colour
) {
	#ifndef DISABLE_TRIANGLES
		std::vector <SDL_Vertex> verts = {
			{SDL_FPoint{point1.x, point1.y}, colour, SDL_FPoint{0}},
			{SDL_FPoint{point2.x, point2.y}, colour, SDL_FPoint{0}},
			{SDL_FPoint{point3.x, point3.y}, colour, SDL_FPoint{0}}
		};

		SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);
	#endif
}
