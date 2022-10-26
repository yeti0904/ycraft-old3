#ifndef YCRAFT_TEXTUREPACKSELECTORMENU_HH
#define YCRAFT_TEXTUREPACKSELECTORMENU_HH

#include "_components.hh"
#include "menuBase.hh"
#include "ui.hh"
#include "settings.hh"

enum class AppState;

namespace Menus {
	class TexturePackSelector : public MenuBase {
		public:
			// variables
			std::string               texturePacksPath;
			std::vector <std::string> texturePacks;
			size_t                    page;
			UI::ButtonArray           options;
			UI::Button                previousButton;
			UI::Button                nextButton;
			UI::Button                backButton;
			UI::Button                reloadButton;
			static constexpr int      itemsPerPage = 5;
			SettingsManager*          settings;

			// functions
			TexturePackSelector();
			void Init(std::string gamePath);
			void LoadPage();
			void Update(AppState& state);
			void Render(SDL_Renderer* renderer, TextComponents& text);
			void Reset();
	};
}

#endif
