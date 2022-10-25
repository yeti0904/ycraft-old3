#include "worldMenu.hh"
#include "constants.hh"
#include "app.hh"
#include "constants.hh"
#include "colours.hh"
#include "util.hh"

Menus::WorldsMenu::WorldsMenu():
	page(0)
{
	MenuBase();

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

	worlds.position        = {45, 45};
	worlds.size            =
		{APP_SCREEN_SIZE_W - worlds.position.x - 60, APP_SCREEN_SIZE_H - 120};
	worlds.selectedOutline = Colours::white;
	worlds.selectedFilled  = Colours::grey;
	worlds.outline         = Colours::black;
	worlds.filled          = Colours::grey;
	worlds.vertical        = true;

	playButton.label         = "Play world";
	playButton.position.x    = newWorldButton.position.x;
	playButton.position.y    = newWorldButton.position.y - 30;
	playButton.size          = {200, 25};
	playButton.outlineColour = Colours::black;
	playButton.filledColour  = Colours::grey;

	previousButton.label         = "<";
	previousButton.size          = {25, 25};
	previousButton.position.x    = worlds.position.x - 30;
	previousButton.position.y
		= ((worlds.size.y / 2) - (backButton.size.y / 2)) + worlds.position.y;
	previousButton.outlineColour = Colours::black;
	previousButton.filledColour  = Colours::grey;

	nextButton.label         = ">";
	nextButton.size          = {25, 25};
	nextButton.position.x = worlds.position.x + 5 + worlds.size.x;
	nextButton.position.y
		= ((worlds.size.y / 2) - (nextButton.size.y / 2)) + worlds.position.y;
	nextButton.outlineColour = Colours::black;
	nextButton.filledColour  = Colours::grey;
}

void Menus::WorldsMenu::Init(std::string gamePath) {
	std::string worldsPath = gamePath + "/maps";
	worldsList = Util::GetFilesInDirectory(worldsPath);
	page = 0;
	LoadPage();
}

void Menus::WorldsMenu::LoadPage() {
	worlds.options = {};

	if (page * itemsPerPage > worldsList.size()) {
		for (int i = 0; i < itemsPerPage; ++i) {
			worlds.options.push_back("");
		}
		return;
	}

	for (size_t i = page * itemsPerPage; i < worldsList.size(); ++i) {
		if (i >= (page * itemsPerPage) + itemsPerPage) {
			break;
		}
		worlds.options.push_back(Util::BaseName(worldsList[i]));
	}
	for (size_t i = worlds.options.size(); i < itemsPerPage; ++i) {
		worlds.options.push_back("");
	}
}

void Menus::WorldsMenu::Update(AppState& state) {
	backButton.outlineColour = backButton.MouseIsOver(mousePosition)?
		Colours::white : Colours::black;
	newWorldButton.outlineColour =
		newWorldButton.MouseIsOver(mousePosition)? Colours::white : Colours::black;
	playButton.outlineColour =
		playButton.MouseIsOver(mousePosition)? Colours::white : Colours::black;
	previousButton.outlineColour =
		previousButton.MouseIsOver(mousePosition)? Colours::white : Colours::black;
	nextButton.outlineColour =
		nextButton.MouseIsOver(mousePosition)? Colours::white : Colours::black;

	if (mousePressed && newWorldButton.MouseIsOver(mousePosition)) {
		state = AppState::NewWorldMenu;
		mousePressed = false;
	}
	if (mousePressed && backButton.MouseIsOver(mousePosition)) {
		state = AppState::TitleScreen;
		mousePressed = false;
	}
	if (mousePressed && playButton.MouseIsOver(mousePosition)) {
		state = AppState::InGame;
		mousePressed = false;
	}
	if (mousePressed) {
		ssize_t worldSelected = worlds.MouseIsOver(mousePosition);
		if (worldSelected >= 0) {
			worlds.set = worldSelected;
		}
	}
	if (mousePressed && previousButton.MouseIsOver(mousePosition)) {
		if (page != 0) {
			-- page;
			LoadPage();
		}
		mousePressed = false;
	}
	if (mousePressed && nextButton.MouseIsOver(mousePosition)) {
		if (page < (worldsList.size() / itemsPerPage)) {
			++ page;
			LoadPage();
		}
		mousePressed = false;
	}

	worlds.UpdateSelected(mousePosition);
}

void Menus::WorldsMenu::Render(SDL_Renderer* renderer, TextComponents& text) {
	// draw background
	SDL_SetRenderDrawColor(renderer, Colours::bg.r, Colours::bg.g, Colours::bg.b, 255);
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

	// draw menu
	backButton.Render(renderer, text);
	newWorldButton.Render(renderer, text);
	playButton.Render(renderer, text);
	previousButton.Render(renderer, text);
	nextButton.Render(renderer, text);
	worlds.Render(renderer, text);
}
