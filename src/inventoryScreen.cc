#include "inventoryScreen.hh"
#include "game.hh"
#include "colours.hh"

InventoryScreen::InventoryScreen():
	inventory(nullptr),
	isItemSelected(false),
	selectedItem{0, 0},
	mousePosition{0, 0},
	mouseClicked(false)
{
	
}

void InventoryScreen::Update(Game& game) {
	
}

void InventoryScreen::HandleEvent(SDL_Event event) {
	
}

void InventoryScreen::Render(SDL_Renderer* renderer, TextComponents& text, Game& game) {
	SDL_Color outline = Colours::white;
	SDL_Color filled  = Colours::grey;

	SDL_SetRenderDrawColor(renderer, filled.r, filled.g, filled.b, filled.a);
	SDL_RenderDrawRect(renderer, &box);
	SDL_SetRenderDrawColor(renderer, outline.r, outline.g, outline.b, outline.a);
	SDL_RenderFillRect(renderer, &box);
}