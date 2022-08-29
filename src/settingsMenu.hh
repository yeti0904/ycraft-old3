#ifndef YCRAFT_SETTINGSMENU_HH
#define YCRAFT_SETTINGSMENU_HH

#include "_components.hh"
#include "ui.hh"
#include "settings.hh"

enum class AppState;

namespace Menus {
	class SettingsMenu {
		public:
			// variables
			UI::Button       backButton;
			UI::Button       applyButton;
			UI::Checkbox     fullscreenCheckbox;
			Vec2             mousePosition;
			bool             mousePressed;
			SettingsManager* settings;

			// functions
			SettingsMenu();
			void Init();
			void HandleEvent(SDL_Event& event);
			bool Update(AppState& state);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};
}

#endif
