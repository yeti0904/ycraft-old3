#include "worldMenu.hh"
#include "constants.hh"
#include "app.hh"
#include "constants.hh"
#include "colours.hh"

Menus::WorldsMenu::WorldsMenu() {
	mousePosition = {0, 0};
	mousePressed  = false;

	backButton.label         = "Back";
	backButton.position.x    = (APP_SCREEN_SIZE_W / 2) - 215;
	backButton.position.y    = APP_SCREEN_SIZE_H - 30;
	backButton.size          = {200, 25};
	backButton.outlineColour = Colours::black;
	backButton.filledColour  = Colours::grey;

	newWorldButton.label         = "Create new world";
	newWorldButton.position.x    = (APP_SCREEN_SIZE_W / 2) + 15;
	newWorldButton.position.y    = APP_SCREEN_SIZE_H - 30;
	newWorldButton.size          = {200, 25};
	newWorldButton.outlineColour = Colours::black;
	newWorldButton.filledColour  = Colours::grey;
}

void Menus::WorldsMenu::Update(AppState& state) {
	backButton.outlineColour = backButton.MouseIsOver(mousePosition)?
		Colours::white : Colours::black;
	newWorldButton.outlineColour =
		newWorldButton.MouseIsOver(mousePosition)? Colours::white : Colours::black;

	if (mousePressed && newWorldButton.MouseIsOver(mousePosition)) {
		state = AppState::NewWorldMenu;
		mousePressed = false;
	}
	if (mousePressed && backButton.MouseIsOver(mousePosition)) {
		state = AppState::TitleScreen;
		mousePressed = false;
	}
}

void Menus::WorldsMenu::Render(SDL_Renderer* renderer, TextComponents& text) {
	// draw background
	SDL_SetRenderDrawColor(renderer, 109, 128, 250, 255);
	SDL_RenderClear(renderer);

	// render menu name
	{
		const std::string menuName = "Worlds";
		Vec2 logoSize = text.GetTextSize(menuName, 2);
		text.RenderText(
			renderer, menuName, {
				(APP_SCREEN_SIZE_W / 2) - (logoSize.x / 2),
				10
			}, 2, true
		);
	}

	// render worlds list
	{
		SDL_Rect worldsListArea;
		worldsListArea.x = 10;
		worldsListArea.y = 40;
		worldsListArea.w = APP_SCREEN_SIZE_W - 20;
		worldsListArea.h = APP_SCREEN_SIZE_H - 80;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &worldsListArea);

		text.RenderText(renderer, "Coming soon", {15, 45}, 1.0, true);
	}

	// draw menu
	backButton.Render(renderer, text);
	newWorldButton.Render(renderer, text);
}
