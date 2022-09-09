#include "settingsMenu.hh"
#include "constants.hh"
#include "app.hh"

Menus::SettingsMenu::SettingsMenu():
	settings(nullptr)
{
	MenuBase();

	backButton.label         = "Back";
	backButton.position.x    = (APP_SCREEN_SIZE_W / 2) - 215;
	backButton.position.y    = APP_SCREEN_SIZE_H - 30;
	backButton.size          = {200, 25};
	backButton.outlineColour = {0, 0, 0, 255};
	backButton.filledColour  = {54, 54, 54, 255};

	applyButton.label         = "Apply settings";
	applyButton.position.x    = (APP_SCREEN_SIZE_W / 2) + 15;
	applyButton.position.y    = APP_SCREEN_SIZE_H - 30;
	applyButton.size          = {200, 25};
	applyButton.outlineColour = {0, 0, 0, 255};
	applyButton.filledColour  = {54, 54, 54, 255};

	fullscreenCheckbox.position.x = 14;
	fullscreenCheckbox.position.y = 44;
	fullscreenCheckbox.size.x     = 8;
	fullscreenCheckbox.size.y     = 9;
	fullscreenCheckbox.colour     = {255, 255, 255, 255};
	
	texturePacksButton.label         = "Texture packs";
	texturePacksButton.position      = {14, 60};
	texturePacksButton.size          = {200, 25};
	texturePacksButton.outlineColour = {0, 0, 0, 255};
	texturePacksButton.filledColour  = {54, 54, 54, 255};
}

void Menus::SettingsMenu::Init() {
	fullscreenCheckbox.activated = settings->settings["fullscreen"] == "true";
}

bool Menus::SettingsMenu::Update(AppState& state) {
	const SDL_Color white = {255, 255, 255, 255};
	const SDL_Color black = {0, 0, 0, 255};

	backButton.outlineColour = backButton.MouseIsOver(mousePosition)? white : black;
	applyButton.outlineColour =
		applyButton.MouseIsOver(mousePosition)? white : black;
	texturePacksButton.outlineColour =
		texturePacksButton.MouseIsOver(mousePosition)? white : black;

	if (mousePressed && applyButton.MouseIsOver(mousePosition)) {
		mousePressed = false;
		settings->Write();
		return true; // update settings
	}
	if (mousePressed && backButton.MouseIsOver(mousePosition)) {
		state        = AppState::TitleScreen;
		mousePressed = false;
	}
	if (mousePressed && fullscreenCheckbox.MouseIsOver(mousePosition)) {
		fullscreenCheckbox.activated     = !fullscreenCheckbox.activated;
		mousePressed                     = false;
		settings->settings["fullscreen"] =
			fullscreenCheckbox.activated? "true" : "false";
	}
	if (mousePressed && texturePacksButton.MouseIsOver(mousePosition)) {
		state        = AppState::TexturePackSelectorMenu;
		mousePressed = false;
	}

	return false;
}

void Menus::SettingsMenu::Render(SDL_Renderer* renderer, TextComponents& text) {
	// draw background
	SDL_SetRenderDrawColor(renderer, 109, 128, 250, 255);
	SDL_RenderClear(renderer);

	// render menu name
	{
		const std::string menuName = "Settings";
		Vec2 logoSize = text.GetTextSize(menuName, 2);
		text.RenderText(
			renderer, menuName, {
				(APP_SCREEN_SIZE_W / 2) - (logoSize.x / 2),
				8
			}, 2, true
		);
	}

	// render worlds list
	{
		SDL_Rect settingsArea;
		settingsArea.x = 10;
		settingsArea.y = 40;
		settingsArea.w = APP_SCREEN_SIZE_W - 20;
		settingsArea.h = APP_SCREEN_SIZE_H - 80;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &settingsArea);
	}

	// draw buttons
	backButton.Render(renderer, text);
	applyButton.Render(renderer, text);
	texturePacksButton.Render(renderer, text);

	// draw settings stuff
	fullscreenCheckbox.Render(renderer);
	text.RenderText(
		renderer, "Enable fullscreen",
		{fullscreenCheckbox.position.x + 12, fullscreenCheckbox.position.y - 3},
		1.0, true
	);
}
