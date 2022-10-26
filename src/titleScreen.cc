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

	creditsButton.label = "Credits";
	creditsButton.outlineColour = Colours::black;
	creditsButton.filledColour  = Colours::grey;
	creditsButton.size          = {200, 25};
	creditsButton.position      = {
		(APP_SCREEN_SIZE_W / 2) - (creditsButton.size.x / 2),
		160
	};



	exitButton.label = "Exit";
	exitButton.outlineColour = Colours::black;
	exitButton.filledColour  = Colours::grey;
	exitButton.size          = {200, 25};
	exitButton.position      = {
		(APP_SCREEN_SIZE_W / 2) - (exitButton.size.x / 2),
		190
	};
}

bool Menus::TitleScreen::Update(AppState& state) {
	playButton.outlineColour = playButton.MouseIsOver(mousePosition)?
		Colours::white : Colours::black;
	exitButton.outlineColour = exitButton.MouseIsOver(mousePosition)?
		Colours::white : Colours::black;
	settingsButton.outlineColour =
		settingsButton.MouseIsOver(mousePosition)? Colours::white : Colours::black;
	creditsButton.outlineColour =
		creditsButton.MouseIsOver(mousePosition)? Colours::white : Colours::black;

	if (mousePressed && playButton.MouseIsOver(mousePosition)) {
		state = AppState::WorldMenu;
		Reset();
	}
	if (mousePressed && settingsButton.MouseIsOver(mousePosition)) {
		state = AppState::SettingsMenu;
		Reset();
	}
	if (mousePressed && creditsButton.MouseIsOver(mousePosition)) {
		state = AppState::CreditsScreen;
		Reset();
	}
	if (mousePressed && exitButton.MouseIsOver(mousePosition)) {
		Reset();
		return false;
	}
	return true;
}

void Menus::TitleScreen::Render(SDL_Renderer* renderer, TextComponents& text) {
	// draw background
	SDL_SetRenderDrawColor(renderer, Colours::bg.r, Colours::bg.g, Colours::bg.b, 255);
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
	creditsButton.Render(renderer, text);
}
