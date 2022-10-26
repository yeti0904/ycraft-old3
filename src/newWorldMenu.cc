#include "newWorldMenu.hh"
#include "app.hh"
#include "constants.hh"
#include "colours.hh"

Menus::NewWorldMenu::NewWorldMenu() {
	MenuBase();

	worldName.outline  = Colours::black;
	worldName.filled   = Colours::grey;
	worldName.position = {15, 60};
	worldName.size     = {APP_SCREEN_SIZE_W - 50, 25};

	worldSizeSelection.options = {
		"Tiny",   // 64x64 (2^6)
		"Small",  // 256x256 (2^8)
		"Medium", // 1024x1024 (2^10)
		"Large",  // 4096x4096 (2^12)
		"Massive" // 16384x16384 (2^14)
	};
	worldSizeSelection.selectedOutline = Colours::white;
	worldSizeSelection.selectedFilled  = Colours::grey;
	worldSizeSelection.outline         = Colours::black;
	worldSizeSelection.filled          = worldSizeSelection.selectedFilled;
	worldSizeSelection.position        = {15, 117};
	worldSizeSelection.size            = {
		APP_SCREEN_SIZE_W - 195,
		25
	};

	backButton.label         = "Back";
	backButton.position.x    = (APP_SCREEN_SIZE_W / 2) - 215;
	backButton.position.y    = APP_SCREEN_SIZE_H - 30;
	backButton.size          = {200, 25};
	backButton.outlineColour = Colours::black;
	backButton.filledColour  = Colours::grey;

	startButton.label         = "START";
	startButton.position.x    = (APP_SCREEN_SIZE_W / 2) + 15;
	startButton.position.y    = APP_SCREEN_SIZE_H - 30;
	startButton.size          = {200, 25};
	startButton.outlineColour = Colours::black;
	startButton.filledColour  = Colours::grey;
}

void Menus::NewWorldMenu::Update(AppState& state) {
	startButton.outlineColour = startButton.MouseIsOver(mousePosition)?
		Colours::white : Colours::black;
	backButton.outlineColour  = backButton.MouseIsOver(mousePosition)?
		Colours::white : Colours::black;

	if (mousePressed && startButton.MouseIsOver(mousePosition)) {
		state = AppState::InGame;
		mousePressed = false;
	}
	if (mousePressed && backButton.MouseIsOver(mousePosition)) {
		state = AppState::WorldMenu;
		mousePressed = false;
	}
	if (mousePressed) {
		worldName.focused = worldName.MouseIsOver(mousePosition);
		worldName.outline = worldName.focused? Colours::white : Colours::black;

		if (worldName.focused) {
			SDL_StartTextInput();
		}
		else {
			SDL_StopTextInput();
		}
	
		ssize_t sizeSelected = worldSizeSelection.MouseIsOver(mousePosition);
		if (sizeSelected >= 0) {
			worldSizeSelection.set = sizeSelected;
		}
	}

	worldSizeSelection.UpdateSelected(mousePosition);
}

void Menus::NewWorldMenu::Render(SDL_Renderer* renderer, TextComponents& text) {
	// draw background
	SDL_SetRenderDrawColor(renderer, Colours::bg.r, Colours::bg.g, Colours::bg.b, 255);
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

	text.RenderText(renderer, "World size", {15, 96}, 1.0, true);
	worldSizeSelection.Render(renderer, text);

	text.RenderText(renderer, "World name", {15, 45}, 1.0, true);
	worldName.Render(renderer, text);
}

void Menus::NewWorldMenu::HandleEvent(SDL_Event& event) {
	switch (event.type) {
		case SDL_MOUSEMOTION: {
			mousePosition.x = event.motion.x;
			mousePosition.y = event.motion.y;
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			if (event.button.button == SDL_BUTTON_LEFT) {
				mousePressed = true;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			if (event.button.button == SDL_BUTTON_LEFT) {
				mousePressed = false;
			}
			break;
		}
		default: {
			if (worldName.focused) {
				worldName.HandleEvent(event);
			}
			break;
		}
	}
}

void Menus::NewWorldMenu::Reset() {
	mousePosition = {0, 0};
	mousePressed  = false;
	worldName.Reset();
}