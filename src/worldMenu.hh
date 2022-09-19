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
			constexpr static int      itemsPerPage = 5;
			UI::Button                backButton;
			UI::Button                newWorldButton;
			UI::Button                playButton;
			UI::Button                previousButton;
			UI::Button                nextButton;
			UI::ButtonArray           worlds;
			std::vector <std::string> worldsList;
			size_t                    page;

			// functions
			WorldsMenu();
			void Init(std::string gamePath);
			void LoadPage();
			void Update(AppState& state);
			void Render(SDL_Renderer* renderer, TextComponents& text);
	};
}

#endif
