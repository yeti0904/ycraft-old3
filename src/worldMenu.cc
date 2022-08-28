#include "worldMenu.hh"
#include "constants.hh"
#include "app.hh"

Menus::WorldsMenu::WorldsMenu() {
	mousePosition = {0, 0};
	mousePressed  = false;

	backButton.label         = "Back";
	backButton.position.x    = (APP_SCREEN_SIZE_W / 2) - 215;
	backButton.position.y    = APP_SCREEN_SIZE_H - 30;
	backButton.size          = {200, 25};
	backButton.outlineColour = {0, 0, 0, 255};
	backButton.filledColour  = {54, 54, 54, 255};

	newWorldButton.label         = "Create new world";
	newWorldButton.position.x    = (APP_SCREEN_SIZE_W / 2) + 15;
	newWorldButton.position.y    = APP_SCREEN_SIZE_H - 30;
	newWorldButton.size          = {200, 25};
	newWorldButton.outlineColour = {0, 0, 0, 255};
	newWorldButton.filledColour  = {54, 54, 54, 255};
}

void Menus::WorldsMenu::HandleEvent(SDL_Event& event) {
	switch (event.type) {
		case SDL_MOUSEMOTION: {
			mousePosition.x = event.motion.x;
			mousePosition.y = event.motion.y;
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			if (event.button.button == SDL_BUTTON_LEFT) {
				mousePressed = true;
				puts("down");
			}
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			if (event.button.button == SDL_BUTTON_LEFT) {
				mousePressed = false;
				puts("up");
			}
			break;
		}
	}
}

void Menus::WorldsMenu::Update(AppState& state) {
	const SDL_Color white = {255, 255, 255, 255};
	const SDL_Color black = {0, 0, 0, 255};

	backButton.outlineColour = backButton.MouseIsOver(mousePosition)? white : black;
	newWorldButton.outlineColour =
		newWorldButton.MouseIsOver(mousePosition)? white : black;

	if (mousePressed && newWorldButton.MouseIsOver(mousePosition)) {
		state = AppState::InGame;
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
