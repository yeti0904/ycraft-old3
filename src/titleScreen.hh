#pragma once
#include "_components.hh"
#include "ui.hh"

enum class AppState;

namespace Menus {
	class TitleScreen {
		public:
			// variables
			UI::Button playButton;
			UI::Button exitButton;
			Vec2       mousePosition;
			bool       mousePressed;
	
			// functions
			TitleScreen();
			void HandleEvent(SDL_Event& event);
			bool Update(AppState& state);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};
}