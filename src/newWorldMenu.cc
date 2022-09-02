#include "newWorldMenu.hh"
#include "app.hh"
#include "constants.hh"

Menus::NewWorldMenu::NewWorldMenu() {
	MenuBase();

	worldSizeSelection.options = {
		"Tiny",   // 64x64 (2^6)
		"Small",  // 256x256 (2^8)
		"Medium", // 1024x1024 (2^10)
		"Large",  // 4096x4096 (2^12)
		"Massive" // 16384x16384 (2^14)
	};
	worldSizeSelection.selectedOutline = {255, 255, 255, 255};
	worldSizeSelection.selectedFilled  = {54, 54, 54, 255};
	worldSizeSelection.outline         = {0, 0, 0, 255};
	worldSizeSelection.filled          = worldSizeSelection.selectedFilled;
	worldSizeSelection.position        = {15, 61};
	worldSizeSelection.size            = {
		APP_SCREEN_SIZE_W - 195,
		25
	};

	backButton.label         = "Back";
	backButton.position.x    = (APP_SCREEN_SIZE_W / 2) - 215;
	backButton.position.y    = APP_SCREEN_SIZE_H - 30;
	backButton.size          = {200, 25};
	backButton.outlineColour = {0, 0, 0, 255};
	backButton.filledColour  = {54, 54, 54, 255};

	startButton.label         = "START";
	startButton.position.x    = (APP_SCREEN_SIZE_W / 2) + 15;
	startButton.position.y    = APP_SCREEN_SIZE_H - 30;
	startButton.size          = {200, 25};
	startButton.outlineColour = {0, 0, 0, 255};
	startButton.filledColour  = {54, 54, 54, 255};
}

void Menus::NewWorldMenu::Update(AppState& state) {
	const SDL_Color white = {255, 255, 255, 255};
	const SDL_Color black = {0, 0, 0, 255};

	startButton.outlineColour = startButton.MouseIsOver(mousePosition)? white : black;
	backButton.outlineColour  = backButton.MouseIsOver(mousePosition)? white : black;

	if (mousePressed && startButton.MouseIsOver(mousePosition)) {
		state = AppState::InGame;
		mousePressed = false;
	}
	if (mousePressed && backButton.MouseIsOver(mousePosition)) {
		state = AppState::WorldMenu;
		mousePressed = false;
	}
	if (mousePressed) {
		ssize_t sizeSelected = worldSizeSelection.MouseIsOver(mousePosition);
		if (sizeSelected >= 0) {
			worldSizeSelection.set = sizeSelected;
		}
	}

	worldSizeSelection.UpdateSelected(mousePosition);
}

void Menus::NewWorldMenu::Render(SDL_Renderer* renderer, TextComponents& text) {
	// draw background
	SDL_SetRenderDrawColor(renderer, 109, 128, 250, 255);
	SDL_RenderClear(renderer);

	// render menu name
	{
		const std::string menuName = "Create new world";
		Vec2 logoSize = text.GetTextSize(menuName, 2.0);
		text.RenderText(
			renderer, menuName, {
				(APP_SCREEN_SIZE_W / 2) - (logoSize.x / 2),
				10
			}, 2.0, true
		);
	}

	// render area
	{
		SDL_Rect worldOptionsArea;
		worldOptionsArea.x = 10;
		worldOptionsArea.y = 40;
		worldOptionsArea.w = APP_SCREEN_SIZE_W - 20;
		worldOptionsArea.h = APP_SCREEN_SIZE_H - 80;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &worldOptionsArea);
	}

	// draw menu
	startButton.Render(renderer, text);
	backButton.Render(renderer, text);

	text.RenderText(renderer, "World size", {15, 45}, 1.0, true);
	worldSizeSelection.Render(renderer, text);
}
