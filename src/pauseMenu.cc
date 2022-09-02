#include "pauseMenu.hh"
#include "app.hh"
#include "game.hh"
#include "constants.hh"

Menus::PauseMenu::PauseMenu():
    mousePosition{0, 0},
    mousePressed(false)
{
	resumeButton.label         = "Resume";
	resumeButton.outlineColour = {0, 0, 0, 255};
	resumeButton.filledColour  = {54, 54, 54, 255};
	resumeButton.size          = {200, 25};
	resumeButton.position      = {5, 50};

	quitButton.label         = "Quit";
	quitButton.outlineColour = {0, 0, 0, 255};
	quitButton.filledColour  = {54, 54, 54, 255};
	quitButton.size          = {200, 25};
	quitButton.position      = {5, 80};
}

void Menus::PauseMenu::HandleEvent(SDL_Event& event) {
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

void Menus::PauseMenu::Update(AppState& state, Game& game) {
	const SDL_Color white = {255, 255, 255, 255};
	const SDL_Color black = {0, 0, 0, 255};

	resumeButton.outlineColour = resumeButton.MouseIsOver(mousePosition)? white : black;
	quitButton.outlineColour = quitButton.MouseIsOver(mousePosition)? white : black;

	if (mousePressed && resumeButton.MouseIsOver(mousePosition)) {
		game.paused  = false;
		mousePressed = false;
		SDL_ShowCursor(SDL_DISABLE);
		return;
	}
	if (mousePressed && quitButton.MouseIsOver(mousePosition)) {
		game.Deinit();
		mousePressed = false;
		state        = AppState::TitleScreen;
		return;
	}
}

void Menus::PauseMenu::Render(SDL_Renderer* renderer, TextComponents& text) {
	// draw background
	SDL_Rect background;
	background.x = 0;
	background.y = 0;
	background.w = APP_SCREEN_SIZE_W;
	background.h = APP_SCREEN_SIZE_H;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50);
	SDL_RenderFillRect(renderer, &background);

	// draw text
	text.RenderText(renderer, "Paused", {5, 5}, 2.0, true);

	// draw buttons
	resumeButton.Render(renderer, text);
	quitButton.Render(renderer, text);	
}
