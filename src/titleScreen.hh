#ifndef YCRAFT_TITLESCREEN_HH
#define YCRAFT_TITLESCREEN_HH

#include "_components.hh"
#include "ui.hh"

enum class AppState;

namespace Menus {
	class TitleScreen {
		public:
			// variables
			UI::Button playButton;
			UI::Button exitButton;
			UI::Button settingsButton;
			Vec2       mousePosition;
			bool       mousePressed;
	
			// functions
			TitleScreen();
			void HandleEvent(SDL_Event& event);
			bool Update(AppState& state);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};
}

#endif
