#ifndef YCRAFT_PAUSEMENU_HH
#define YCRAFT_PAUSEMENU_HH

#include "_components.hh"
#include "ui.hh"

enum class AppState;
class Game;

namespace Menus {
    class PauseMenu {
        public:
            // variables
            UI::Button resumeButton;
            UI::Button quitButton;
            Vec2       mousePosition;
            bool       mousePressed;

            // functions
            PauseMenu();
            void HandleEvent(SDL_Event& event);
            void Update(AppState& state, Game& game);
            void Render(SDL_Renderer* renderer, TextComponents& text);
    };
}

#endif
