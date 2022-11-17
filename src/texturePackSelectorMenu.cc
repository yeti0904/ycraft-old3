#include "texturePackSelectorMenu.hh"
#include "app.hh"
#include "util.hh"
#include "constants.hh"
#include "colours.hh"
#include "mouse.hh"

Menus::TexturePackSelector::TexturePackSelector():
	page(0)
{
	MenuBase();

	options.size            = {200, 25 * itemsPerPage};
	options.selectedOutline = Colours::white;
	options.selectedFilled  = Colours::grey;
	options.outline         = Colours::black;
	options.filled          = Colours::grey;
	options.position        = {
		(APP_SCREEN_SIZE_W / 2) - (options.size.x / 2),
		(APP_SCREEN_SIZE_H / 2) - ((int) options.size.y / 2)
	};
	options.vertical        = true;

	backButton.label         = "Back";
	backButton.position.x    = (APP_SCREEN_SIZE_W / 2) - 215;
	backButton.position.y    = APP_SCREEN_SIZE_H - 30;
	backButton.size          = {200, 25};
	backButton.outlineColour = Colours::black;
	backButton.filledColour  = Colours::grey;

	reloadButton.label         = "Reload list";
	reloadButton.position.x    = (APP_SCREEN_SIZE_W / 2) + 15;
	reloadButton.position.y    = APP_SCREEN_SIZE_H - 30;
	reloadButton.size          = {200, 25};
	reloadButton.outlineColour = Colours::black;
	reloadButton.filledColour  = Colours::grey;

	previousButton.label         = "<";
	previousButton.size          = {25, 25};
	previousButton.position.x    = options.position.x - 30;
	previousButton.position.y
		= ((options.size.y / 2) - (backButton.size.y / 2)) + options.position.y;
	previousButton.outlineColour = Colours::black;
	previousButton.filledColour  = Colours::grey;

	nextButton.label         = ">";
	nextButton.size          = {25, 25};
	nextButton.position.x = options.position.x + 5 + options.size.x;
	nextButton.position.y
		= ((options.size.y / 2) - (nextButton.size.y / 2)) + options.position.y;
	nextButton.outlineColour = Colours::black;
	nextButton.filledColour  = Colours::grey;
}

void Menus::TexturePackSelector::Init(std::string gamePath) {
	texturePacksPath = gamePath + "/texpacks";
	texturePacks     = Util::GetFilesInDirectory(texturePacksPath);
	page             = 0;
	LoadPage();
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
	previousButton.outlineColour =
		previousButton.MouseIsOver(Mouse::Position())? Colours::white : Colours::black;
	nextButton.outlineColour = nextButton.MouseIsOver(Mouse::Position())?
		Colours::white : Colours::black;
	backButton.outlineColour = backButton.MouseIsOver(Mouse::Position())?
		Colours::white : Colours::black;
	reloadButton.outlineColour =
		reloadButton.MouseIsOver(Mouse::Position())? Colours::white : Colours::black;

	if (Mouse::Pressed() && previousButton.MouseIsOver(Mouse::Position())) {
		if (page != 0) {
			-- page;
			LoadPage();
		}
	}
	if (Mouse::Pressed() && nextButton.MouseIsOver(Mouse::Position())) {
		if (page < (texturePacks.size() / itemsPerPage)) {
			++ page;
			LoadPage();
		}
	}
	if (Mouse::Pressed() && backButton.MouseIsOver(Mouse::Position())) {
		state        = AppState::SettingsMenu;
		Reset();
	}
	if (Mouse::Pressed() && reloadButton.MouseIsOver(Mouse::Position())) {
		texturePacks = Util::GetFilesInDirectory(texturePacksPath);
	}
	if (Mouse::Pressed()) {
		ssize_t texturePackSelected = options.MouseIsOver(Mouse::Position());
		if (texturePackSelected >= 0) {
			options.set = texturePackSelected;
		}
	}

	options.UpdateSelected(Mouse::Position());
}

void Menus::TexturePackSelector::Render(SDL_Renderer* renderer, TextComponents& text) {
	// draw background
	SDL_SetRenderDrawColor(renderer, Colours::bg.r, Colours::bg.g, Colours::bg.b, 255);
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

void Menus::TexturePackSelector::Reset() {
	page = 0;
	LoadPage();
}
