#ifndef YCRAFT_UI_HH
#define YCRAFT_UI_HH

#include "_components.hh"
#include "types.hh"
#include "text.hh"

namespace UI {
	class UIElement {
		public:
			// variables
			Vec2 position;
			Vec2 size;

			// functions
			UIElement():
				position{0, 0},
				size{0, 0}
			{}
	};

	class Button : public UIElement {
		public:
			// variables
			std::string label;
			SDL_Color   outlineColour;
			SDL_Color   filledColour;

			// functions
			Button() {
				UIElement();
			}
			bool MouseIsOver(Vec2 cursor);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};

	class Checkbox : public UIElement {
		public:
			// variables
			SDL_Color colour;
			bool      activated;

			// functions
			Checkbox():
				activated(false)
			{
				UIElement();
			}
			bool MouseIsOver(Vec2 cursor);
			void Render(SDL_Renderer* renderer);	
	};

	class ButtonArray : public UIElement {
		// a form of selection, you can only select 1 at a time
		public:
			// variables
			SDL_Color                 selectedOutline;
			SDL_Color                 selectedFilled;
			SDL_Color                 outline;
			SDL_Color                 filled;
			std::vector <std::string> options;
			ssize_t                   selected;
			ssize_t                   set;
			bool                      vertical;
		
			ButtonArray():
				selected(-1),
				set(0),
				vertical(false)
			{
				UIElement();
			}
			ssize_t MouseIsOver(Vec2 cursor);
			void    Render(SDL_Renderer* renderer, TextComponents& text);
			void    UpdateSelected(Vec2 cursor);
	};
}

#endif
