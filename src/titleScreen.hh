#ifndef YCRAFT_TITLESCREEN_HH
#define YCRAFT_TITLESCREEN_HH

#include "_components.hh"
#include "ui.hh"
#include "menuBase.hh"

enum class AppState;

namespace Menus {
	class TitleScreen : public MenuBase {
		public:
			// variables
			UI::Button playButton;
			UI::Button exitButton;
			UI::Button settingsButton;
			UI::Button creditsButton;
	
			// functions
			TitleScreen();
			bool Update(AppState& state);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};
}

#endif
