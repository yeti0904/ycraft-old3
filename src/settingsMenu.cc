#include "settingsMenu.hh"
#include "constants.hh"
#include "app.hh"
#include "colours.hh"

Menus::SettingsMenu::SettingsMenu():
	settings(nullptr)
{
	MenuBase();

	backButton.label         = "Back";
	backButton.position.x    = (APP_SCREEN_SIZE_W / 2) - 215;
	backButton.position.y    = APP_SCREEN_SIZE_H - 30;
	backButton.size          = {200, 25};
	backButton.outlineColour = Colours::black;
	backButton.filledColour  = Colours::grey;

	applyButton.label         = "Apply settings";
	applyButton.position.x    = (APP_SCREEN_SIZE_W / 2) + 15;
	applyButton.position.y    = APP_SCREEN_SIZE_H - 30;
	applyButton.size          = {200, 25};
	applyButton.outlineColour = Colours::black;
	applyButton.filledColour  = Colours::grey;

	fullscreenCheckbox.position.x = 14;
	fullscreenCheckbox.position.y = 44;
	fullscreenCheckbox.size.x     = 8;
	fullscreenCheckbox.size.y     = 9;
	fullscreenCheckbox.colour     = Colours::white;
	
	texturePacksButton.label         = "Texture packs";
	texturePacksButton.position      = {14, 60};
	texturePacksButton.size          = {200, 25};
	texturePacksButton.outlineColour = Colours::black;
	texturePacksButton.filledColour  = Colours::grey;
}

void Menus::SettingsMenu::Init() {
	fullscreenCheckbox.activated = settings->settings["fullscreen"] == "true";
}

bool Menus::SettingsMenu::Update(AppState& state) {
	backButton.outlineColour = backButton.MouseIsOver(mousePosition)?
		Colours::white : Colours::black;
	applyButton.outlineColour =
		applyButton.MouseIsOver(mousePosition)? Colours::white : Colours::black;
	texturePacksButton.outlineColour =
		texturePacksButton.MouseIsOver(mousePosition)? Colours::white : Colours::black;

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
