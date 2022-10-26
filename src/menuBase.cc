#include "menuBase.hh"

MenuBase::MenuBase():
	mousePosition{0, 0},
	mousePressed(false)
{
	
}

void MenuBase::HandleEvent(SDL_Event& event) {
	switch (event.type) {
		case SDL_MOUSEMOTION: {
			mousePosition.x = event.motion.x;
			mousePosition.y = event.motion.y;
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			if (event.button.button == SDL_BUTTON_LEFT) {
				mousePressed = true;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			if (event.button.button == SDL_BUTTON_LEFT) {
				mousePressed = false;
			}
			break;
		}
	}
}

void MenuBase::Reset() {
	mousePosition = {0, 0};
	mousePressed  = false;
}