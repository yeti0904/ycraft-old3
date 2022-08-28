#ifndef YCRAFT_TEXT_HH
#define YCRAFT_TEXT_HH

#include "_components.hh"
#include "video.hh"
#include "types.hh"

class TextComponents {
	public:
		// variables
		TTF_Font* font;

		// functions
		TextComponents();
		void Init(std::string fontPath);
		void Free();
		void RenderText(
			SDL_Renderer* renderer, std::string text,
			Vec2 pos, float size, bool shadow
		);
		Vec2 GetTextSize(std::string text, float size);
};

#endif
