#ifndef YCRAFT_VIDEO_HH
#define YCRAFT_VIDEO_HH

#include "_components.hh"
#include "settings.hh"
#include "types.hh"

class VideoComponents {
	public:
		// variables
		SDL_Window*   window;
		SDL_Renderer* renderer;

		// functions
		VideoComponents() {}
		void Init();
		void DrawTriangle(FVec2 point1, FVec2 point2, FVec2 point3, SDL_Color colour);
		void Free();
};

#endif
