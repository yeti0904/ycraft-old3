#ifndef YCRAFT_WORLDMENU_HH
#define YCRAFT_WORLDMENU_HH
#include "_components.hh"
#include "text.hh"
#include "ui.hh"

enum class AppState;

namespace Menus {
	class WorldsMenu {
		public:
			// variables
			UI::Button backButton;
			UI::Button newWorldButton;
			Vec2       mousePosition;
			bool       mousePressed;

			// functions
			WorldsMenu();
			void HandleEvent(SDL_Event& event);
			void Update(AppState& state);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};
}

#endif
