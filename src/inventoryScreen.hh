#ifndef YCRAFT_INVENTORYSCREEN_HH
#define YCRAFT_INVENTORYSCREEN_HH

#include "_components.hh"
#include "types.hh"
#include "inventory.hh"
#include "text.hh"

class Game;

class InventoryScreen {
	public:
		// variables
		Rect       box;
		Inventory* inventory;
		bool       isItemSelected;
		UVec2      selectedItem;
		UVec2      mousePosition;
		bool       mouseClicked;

		// functions
		InventoryScreen();
		void Update(Game& game);
		void HandleEvent(SDL_Event event);
		void Render(SDL_Renderer* renderer, TextComponents& text, Game& game);
};

#endif