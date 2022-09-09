#include "titleScreen.hh"
#include "constants.hh"
#include "app.hh"
#include "colours.hh"

Menus::TitleScreen::TitleScreen() {
	MenuBase();

	playButton.label         = "Play";
	playButton.outlineColour = Colours::black;
	playButton.filledColour  = Colours::grey;
	playButton.size          = {200, 25};
	playButton.position      = {
		(APP_SCREEN_SIZE_W / 2) - (playButton.size.x / 2),
		100
	};

	settingsButton.label = "Settings";
	settingsButton.outlineColour = Colours::black;
	settingsButton.filledColour  = Colours::grey;
	settingsButton.size          = {200, 25};
	settingsButton.position      = {
		(APP_SCREEN_SIZE_W / 2) - (settingsButton.size.x / 2),
		130
	};

	exitButton.label = "Exit";
	exitButton.outlineColour = Colours::black;
	exitButton.filledColour  = Colours::grey;
	exitButton.size          = {200, 25};
	exitButton.position      = {
		(APP_SCREEN_SIZE_W / 2) - (exitButton.size.x / 2),
		160
	};
}

bool Menus::TitleScreen::Update(AppState& state) {
	playButton.outlineColour = playButton.MouseIsOver(mousePosition)?
		Colours::white : Colours::black;
	exitButton.outlineColour = exitButton.MouseIsOver(mousePosition)?
		Colours::white : Colours::black;
	settingsButton.outlineColour =
		settingsButton.MouseIsOver(mousePosition)? Colours::white : Colours::black;

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
