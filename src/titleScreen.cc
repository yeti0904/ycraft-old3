#include "titleScreen.hh"
#include "constants.hh"
#include "app.hh"

Menus::TitleScreen::TitleScreen() {
	MenuBase();

	playButton.label         = "Play";
	playButton.outlineColour = {0, 0, 0, 255};
	playButton.filledColour  = {54, 54, 54, 255};
	playButton.size          = {200, 25};
	playButton.position      = {
		(APP_SCREEN_SIZE_W / 2) - (playButton.size.x / 2),
		100
	};

	settingsButton.label = "Settings";
	settingsButton.outlineColour = {0, 0, 0, 255};
	settingsButton.filledColour  = {54, 54, 54, 255};
	settingsButton.size          = {200, 25};
	settingsButton.position      = {
		(APP_SCREEN_SIZE_W / 2) - (settingsButton.size.x / 2),
		130
	};

	exitButton.label = "Exit";
	exitButton.outlineColour = {0, 0, 0, 255};
	exitButton.filledColour  = {54, 54, 54, 255};
	exitButton.size          = {200, 25};
	exitButton.position      = {
		(APP_SCREEN_SIZE_W / 2) - (exitButton.size.x / 2),
		160
	};
}

bool Menus::TitleScreen::Update(AppState& state) {
	const SDL_Color white = {255, 255, 255, 255};
	const SDL_Color black = {0, 0, 0, 255};

	playButton.outlineColour = playButton.MouseIsOver(mousePosition)? white : black;
	exitButton.outlineColour = exitButton.MouseIsOver(mousePosition)? white : black;
	settingsButton.outlineColour =
		settingsButton.MouseIsOver(mousePosition)? white : black;

	if (mousePressed && playButton.MouseIsOver(mousePosition)) {
		state = AppState::WorldMenu;
		mousePressed = false;
	}
	if (mousePressed && settingsButton.MouseIsOver(mousePosition)) {
		state = AppState::SettingsMenu;
		mousePressed = false;
	}
	if (mousePressed && exitButton.MouseIsOver(mousePosition)) {
		mousePressed = false;
		return false;
	}
	return true;
}

void Menus::TitleScreen::Render(SDL_Renderer* renderer, TextComponents& text) {
	// draw background
	SDL_SetRenderDrawColor(renderer, 109, 128, 250, 255);
	SDL_RenderClear(renderer);

	// render title screen
	{
		Vec2 logoSize = text.GetTextSize(APP_NAME, 2.0);
		text.RenderText(
			renderer, APP_NAME, {
				(APP_SCREEN_SIZE_W / 2) - (logoSize.x / 2),
				50
			}, 2.0, true
		);
	}

	// draw menu
	playButton.Render(renderer, text);
	exitButton.Render(renderer, text);
	settingsButton.Render(renderer, text);
}
