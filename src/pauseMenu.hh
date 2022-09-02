#ifndef YCRAFT_PAUSEMENU_HH
#define YCRAFT_PAUSEMENU_HH

#include "_components.hh"
#include "ui.hh"
#include "menuBase.hh"

enum class AppState;
class Game;

namespace Menus {
    class PauseMenu : public MenuBase {
        public:
            // variables
            UI::Button resumeButton;
            UI::Button quitButton;

            // functions
            PauseMenu();
            void Update(AppState& state, Game& game);
            void Render(SDL_Renderer* renderer, TextComponents& text);
    };
}

#endif
