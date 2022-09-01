#ifndef YCRAFT_NEWWORLDMENU_HH
#define YCRAFT_NEWWORLDMENU_HH

#include "_components.hh"
#include "ui.hh"
#include "level.hh"

enum class AppState;

namespace Menus {
	class NewWorldMenu {
		public:
			// variables
			UI::ButtonArray worldSizeSelection;
			UI::Button      backButton;
			UI::Button      startButton;
			Vec2            mousePosition;
			bool            mousePressed;
	
			// functions
			NewWorldMenu();
			void HandleEvent(SDL_Event& event);
			void Update(AppState& state);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};
}

#endif
