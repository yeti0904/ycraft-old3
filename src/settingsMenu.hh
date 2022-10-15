#ifndef YCRAFT_SETTINGSMENU_HH
#define YCRAFT_SETTINGSMENU_HH

#include "_components.hh"
#include "ui.hh"
#include "settings.hh"
#include "menuBase.hh"

enum class AppState;

namespace Menus {
	class SettingsMenu : public MenuBase {
		public:
			// variables
			UI::Button       backButton;
			//UI::Button       applyButton;
			UI::Checkbox     fullscreenCheckbox;
			UI::Button       texturePacksButton;
			UI::Checkbox     musicCheckbox;
			SettingsManager* settings;

			// functions
			SettingsMenu();
			void Init();
			bool Update(AppState& state);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};
}

#endif
