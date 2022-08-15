#pragma once
#include "_components.hh"

class VideoComponents {
	public:
		// variables
		SDL_Window*   window;
		SDL_Renderer* renderer;

		// functions
		VideoComponents() {}
		void Init();
		void Free();
};
