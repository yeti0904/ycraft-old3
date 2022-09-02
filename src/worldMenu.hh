#ifndef YCRAFT_WORLDMENU_HH
#define YCRAFT_WORLDMENU_HH

#include "_components.hh"
#include "text.hh"
#include "ui.hh"
#include "menuBase.hh"

enum class AppState;

namespace Menus {
	class WorldsMenu : public MenuBase {
		public:
			// variables
			UI::Button backButton;
			UI::Button newWorldButton;

			// functions
			WorldsMenu();
			void Update(AppState& state);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};
}

#endif
