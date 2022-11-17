#ifndef YCRAFT_CREDITSSCREEN_HH
#define YCRAFT_CREDITSSCREEN_HH

#include "_components.hh"
#include "ui.hh"
#include "menuBase.hh"

enum class AppState;

namespace Menus {
	class CreditsScreen : public MenuBase {
		public:
			// variables
			UI::Button                backButton;
			std::vector <std::string> credits;

			// functions
			CreditsScreen();
			void Update(AppState& state);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};
}

#endif
