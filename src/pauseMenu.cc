#include "pauseMenu.hh"
#include "app.hh"
#include "game.hh"
#include "constants.hh"
#include "colours.hh"
#include "mouse.hh"

Menus::PauseMenu::PauseMenu() {
	MenuBase();

	resumeButton.label         = "Resume";
	resumeButton.outlineColour = Colours::black;
	resumeButton.filledColour  = Colours::grey;
	resumeButton.size          = {200, 25};
	resumeButton.position      = {5, 50};

	quitButton.label         = "Save & Quit";
	quitButton.outlineColour = Colours::black;
	quitButton.filledColour  = Colours::grey;
	quitButton.size          = {200, 25};
	quitButton.position      = {5, 80};
}

void Menus::PauseMenu::Update(AppState& state, Game& game) {
	resumeButton.outlineColour = resumeButton.MouseIsOver(Mouse::Position())?
		Colours::white : Colours::black;
	quitButton.outlineColour = quitButton.MouseIsOver(Mouse::Position())?
		Colours::white : Colours::black;

	if (Mouse::Pressed() && resumeButton.MouseIsOver(Mouse::Position())) {
		game.gameState  = GameState::Running;
		Reset();
		SDL_ShowCursor(SDL_DISABLE);
		return;
	}
	if (Mouse::Pressed() && quitButton.MouseIsOver(Mouse::Position())) {
		game.level.Save();
		game.Deinit();
		Reset();
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
