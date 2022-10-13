#include "creditsScreen.hh"
#include "app.hh"
#include "colours.hh"
#include "constants.hh"

Menus::CreditsScreen::CreditsScreen() {
	MenuBase();

	backButton.label         = "Back";
	backButton.outlineColour = Colours::black;
	backButton.filledColour  = Colours::grey;
	backButton.size          = {200, 25};
	backButton.position      = {
		5, APP_SCREEN_SIZE_H - backButton.size.y - 5
	};

	credits = {
		"programming: MESYETI",
		"art: MESYETI, LordOfTrident",
		"font: Zeh Fernando",
		"music: LoubiTek"
	};
}

void Menus::CreditsScreen::Update(AppState& state) {
	backButton.outlineColour = backButton.MouseIsOver(mousePosition)?
		Colours::white : Colours::black;

	if (mousePressed && backButton.MouseIsOver(mousePosition)) {
		state        = AppState::TitleScreen;
		mousePressed = false;
	}
}

void Menus::CreditsScreen::Render(SDL_Renderer* renderer, TextComponents& text) {
	// draw background
	SDL_SetRenderDrawColor(renderer, 109, 128, 250, 255);
	SDL_RenderClear(renderer);

	// render credits
	Vec2 pos = {5, 5};
	for (auto& credit : credits) {
		text.RenderText(renderer, credit, pos, 1.0, true);
		pos.y += text.GetTextSize(credit, 1.0).y + 5;
	}

	// render buttons
	backButton.Render(renderer, text);
}