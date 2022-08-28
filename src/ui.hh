#ifndef YCRAFT_UI_HH
#define YCRAFT_UI_HH

#include "_components.hh"
#include "types.hh"
#include "text.hh"

namespace UI {
	class UIElement {
		public:
			Vec2 position;
			Vec2 size;

			UIElement():
				position{0, 0},
				size{0, 0}
			{}
	};

	class Button : public UIElement {
		public:
			std::string label;
			SDL_Color   outlineColour;
			SDL_Color   filledColour;

			Button() {
				UIElement();
			}
			bool MouseIsOver(Vec2 cursor);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};
}

#endif
