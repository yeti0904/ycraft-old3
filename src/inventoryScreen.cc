#include "inventoryScreen.hh"
#include "game.hh"
#include "colours.hh"
#include "constants.hh"
#include "app.hh"
#include "collision.hh"

InventoryScreen::InventoryScreen():
	inventory(nullptr),
	isItemSelected(false),
	selectedItem{0, 0},
	mousePosition{0, 0},
	mousePressed(false),
	parent(nullptr)
{
	box.w = 150;
	box.h = 150;
	box.x = (APP_SCREEN_SIZE_W / 2) - (box.w / 2);
	box.y = (APP_SCREEN_SIZE_H / 2) - (box.h / 2);
}

void InventoryScreen::Update() {
	
}

void InventoryScreen::HandleEvent(SDL_Event event) {
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
			if (mouseHoveringOver.x != -1) {
				if (isItemSelected) {
					isItemSelected = false;
					auto item = inventory->inventory[oldPos.y][oldPos.x];
					if (
						!inventory->inventory
						[mouseHoveringOver.y][mouseHoveringOver.x].empty
					) {
						inventory->inventory[oldPos.y][oldPos.x] =
							inventory->inventory[mouseHoveringOver.y][mouseHoveringOver.x];
					}
					else {
						inventory->inventory[oldPos.y][oldPos.x] = {true, 0, 0};
					}
					inventory->inventory[mouseHoveringOver.y][mouseHoveringOver.x] =
						item;
				}
				else {
					if (
						inventory->inventory[mouseHoveringOver.y][mouseHoveringOver.x]
						.empty
					) {
						break;
					}
					isItemSelected = true;
					selectedItem   = {
						(uint32_t) mouseHoveringOver.x, (uint32_t) mouseHoveringOver.y
					};
					oldPos         = mouseHoveringOver;
				}
			}
			break;
		}
	    case SDL_KEYUP: {
	        switch (event.key.keysym.scancode) {
	            case SDL_SCANCODE_E: {
	                parent->gameState = GameState::Running;
	                SDL_ShowCursor(SDL_DISABLE);
	                break;
	            }
	            default: break;
	        }
	    }
	}
}

void InventoryScreen::Render(SDL_Renderer* renderer, TextComponents& text) {
	SDL_Color outline = Colours::white;
	SDL_Color filled  = Colours::lightgrey;

	SDL_SetRenderDrawColor(renderer, filled.r, filled.g, filled.b, filled.a);
	SDL_RenderFillRect(renderer, &box);
	SDL_SetRenderDrawColor(renderer, outline.r, outline.g, outline.b, outline.a);
	SDL_RenderDrawRect(renderer, &box);

	// render inventory spots
	Vec2 startPos = {box.x + 2, box.y + box.w - 2};
	mouseHoveringOver = {-1, -1};
	for (ssize_t i = inventory->inventory.size() - 1; i >= 0; --i) {
	    startPos.y -= GAME_BLOCK_SIZE;

	    for (size_t j = 0; j < inventory->inventory[i].size(); ++j) {
	        auto& item = inventory->inventory[i][j];
            Rect  itemBox = {startPos.x, startPos.y, GAME_BLOCK_SIZE, GAME_BLOCK_SIZE};
            itemBox.x = startPos.x + (GAME_BLOCK_SIZE * j);

			if (
				Collision::PointVsRect(
					{(float) mousePosition.x, (float) mousePosition.y},
					{
						(float) itemBox.x, (float) itemBox.y,
						(float) itemBox.w, (float) itemBox.h
					}
				)
			) {
				mouseHoveringOver = {(int) j, (int) i};
			}
	        
            if (
                !item.empty &&
                (
                	!isItemSelected || (isItemSelected &&
                	(j != selectedItem.x || i != selectedItem.y))
                )
            ) {
	            parent->app->gameTextures.RenderTile(
	                renderer, parent->blockdefs.defs[item.block].textureID,
	                {itemBox.x, itemBox.y}
	            );
	        }
	        SDL_SetRenderDrawColor(renderer, outline.r, outline.g, outline.b, outline.a);
	        SDL_RenderDrawRect(renderer, &itemBox);
	    }
	}

	if (isItemSelected) {
		auto item = inventory->inventory[selectedItem.y][selectedItem.x];
		parent->app->gameTextures.RenderTile(
			renderer, parent->blockdefs.defs[item.block].textureID,
			{(int) mousePosition.x, (int) mousePosition.y}
		);
	}
}