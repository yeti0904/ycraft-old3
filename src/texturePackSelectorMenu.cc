#include "texturePackSelectorMenu.hh"
#include "app.hh"
#include "util.hh"
#include "constants.hh"

Menus::TexturePackSelector::TexturePackSelector():
	page(0)
{
	MenuBase();

	options.size            = {200, 25 * itemsPerPage};
	options.selectedOutline = {255, 255, 255, 255};
	options.selectedFilled  = {54, 54, 54, 255};
	options.outline         = {0, 0, 0, 255};
	options.filled          = {54, 54, 54, 255};
	options.position        = {
		(APP_SCREEN_SIZE_W / 2) - (options.size.x / 2),
		(APP_SCREEN_SIZE_H / 2) - ((int) options.size.y / 2)
	};
	options.vertical        = true;

	backButton.label         = "Back";
	backButton.position.x    = (APP_SCREEN_SIZE_W / 2) - 215;
	backButton.position.y    = APP_SCREEN_SIZE_H - 30;
	backButton.size          = {200, 25};
	backButton.outlineColour = {0, 0, 0, 255};
	backButton.filledColour  = {54, 54, 54, 255};

	reloadButton.label         = "Reload list";
	reloadButton.position.x    = (APP_SCREEN_SIZE_W / 2) + 15;
	reloadButton.position.y    = APP_SCREEN_SIZE_H - 30;
	reloadButton.size          = {200, 25};
	reloadButton.outlineColour = {0, 0, 0, 255};
	reloadButton.filledColour  = {54, 54, 54, 255};

	previousButton.label         = "<";
	previousButton.size          = {25, 25};
	previousButton.position.x    = options.position.x - 30;
	previousButton.position.y
		= ((options.size.y / 2) - (backButton.size.y / 2)) + options.position.y;
	previousButton.outlineColour = {0, 0, 0, 255};
	previousButton.filledColour  = {54, 54, 54, 255};

	nextButton.label         = ">";
	nextButton.size          = {25, 25};
	nextButton.position.x = options.position.x + 5 + options.size.x;
	nextButton.position.y
		= ((options.size.y / 2) - (nextButton.size.y / 2)) + options.position.y;
	nextButton.outlineColour = {0, 0, 0, 255};
	nextButton.filledColour  = {54, 54, 54, 255};
}

void Menus::TexturePackSelector::Init(std::string gamePath) {
	texturePacksPath = gamePath + "/texpacks";
	texturePacks     = Util::GetFilesInDirectory(texturePacksPath);
	LoadPage();
	page             = 0;
}

void Menus::TexturePackSelector::LoadPage() {
	options.options = {};
	
	if (page * itemsPerPage > texturePacks.size()) {
		for (int i = 0; i < itemsPerPage; ++i) {
			options.options.push_back("");
		}
		return;
	}

	for (size_t i = page * itemsPerPage; i < texturePacks.size(); ++i) {
		if (i >= (page * itemsPerPage) + itemsPerPage) {
			break;
		}
		options.options.push_back(Util::BaseName(texturePacks[i]));
	}
	for (size_t i = options.options.size(); i < itemsPerPage; ++i) {
		options.options.push_back("");
	}

	options.set = -1;
	for (size_t i = 0; i < options.options.size(); ++i) {
		if (options.options[i] == settings->settings["texturePack"]) {
			options.set = (ssize_t) i;
			break;
		}
	}
}

void Menus::TexturePackSelector::Update(AppState& state) {
	const SDL_Color white = {255, 255, 255, 255};
	const SDL_Color black = {0, 0, 0, 255};

	previousButton.outlineColour =
		previousButton.MouseIsOver(mousePosition)? white : black;
	nextButton.outlineColour = nextButton.MouseIsOver(mousePosition)? white : black;
	backButton.outlineColour = backButton.MouseIsOver(mousePosition)? white : black;
	reloadButton.outlineColour =
		reloadButton.MouseIsOver(mousePosition)? white : black;

	if (mousePressed && previousButton.MouseIsOver(mousePosition)) {
		if (page != 0) {
			-- page;
			LoadPage();
		}
		mousePressed = false;
	}
	if (mousePressed && nextButton.MouseIsOver(mousePosition)) {
		if (page < (texturePacks.size() / itemsPerPage)) {
			++ page;
			LoadPage();
		}
		mousePressed = false;
	}
	if (mousePressed && backButton.MouseIsOver(mousePosition)) {
		state        = AppState::SettingsMenu;
		mousePressed = false;
	}
	if (mousePressed && reloadButton.MouseIsOver(mousePosition)) {
		texturePacks = Util::GetFilesInDirectory(texturePacksPath);
		mousePressed = false;
	}
	if (mousePressed) {
		ssize_t texturePackSelected = options.MouseIsOver(mousePosition);
		if (texturePackSelected >= 0) {
			options.set = texturePackSelected;
		}
	}

	options.UpdateSelected(mousePosition);
}

void Menus::TexturePackSelector::Render(SDL_Renderer* renderer, TextComponents& text) {
	// draw background
	SDL_SetRenderDrawColor(renderer, 109, 128, 250, 255);
	SDL_RenderClear(renderer);

	// render menu name
	{
		const char* menuName = "Texture packs";
		Vec2 menuNameSize = text.GetTextSize(menuName, 2.0);
		text.RenderText(
			renderer, menuName, {
				(APP_SCREEN_SIZE_W / 2) - (menuNameSize.x / 2),
				10
			}, 2.0, true
		);
	}

	options.Render(renderer, text);
	previousButton.Render(renderer, text);
	nextButton.Render(renderer, text);
	backButton.Render(renderer, text);
	reloadButton.Render(renderer, text);
}
