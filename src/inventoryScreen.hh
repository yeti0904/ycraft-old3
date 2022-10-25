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
		bool       mousePressed;
		Vec2       mouseHoveringOver;
		Vec2       oldPos;
		Game*      parent;

		// functions
		InventoryScreen();
		void Update();
		void HandleEvent(SDL_Event event);
		void Render(SDL_Renderer* renderer, TextComponents& text);
};

#endif