#ifndef YCRAFT_NEWWORLDMENU_HH
#define YCRAFT_NEWWORLDMENU_HH

#include "_components.hh"
#include "ui.hh"
#include "level.hh"
#include "menuBase.hh"

enum class AppState;

namespace Menus {
	class NewWorldMenu : public MenuBase {
		public:
			// variables
			UI::ButtonArray worldSizeSelection;
			UI::Button      backButton;
			UI::Button      startButton;
	
			// functions
			NewWorldMenu();
			void Update(AppState& state);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};
}

#endif