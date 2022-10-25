#include "game.hh"
#include "app.hh"
#include "constants.hh"
#include "colours.hh"
#include "app.hh"
#include "commands.hh"
#include "util.hh"

Game::Game() {
	RegisterCommands(commands);
}

void Game::Init(UVec2 levelSize, bool generate) {
	blockdefs.Create(0, "Air",    0,  BlockType::Gas);
	blockdefs.Create(1, "Stone",  4,  BlockType::Solid);
	blockdefs.Create(2, "Dirt",   1,  BlockType::Solid);
	blockdefs.Create(3, "Grass",  0,  BlockType::Solid);
	blockdefs.Create(4, "Bricks", 12, BlockType::Solid);
	blockdefs.Create(5, "Cobble", 5,  BlockType::Solid);

	/*camera.x = 0;
	camera.y = 0;
	
	player.position.x =
	    ((APP_SCREEN_SIZE_W / GAME_BLOCK_SIZE) / 2);
	player.position.y =
	    ((APP_SCREEN_SIZE_H / GAME_BLOCK_SIZE) / 2);*/

	mousePosition = {0, 0};
	mouseDown     = false;

	gameState        = GameState::Running;
	blockHighlighted = false;
	highlightedBlock = {0, 0};
    
	// player.position.x = 5;
	// player.position.y = 5;

	if (generate) {
		level.size = levelSize;
		level.Generate();
	}

	SpawnPlayer();
	UpdateCamera();

	chatbox.outline  = Colours::nothing;
	chatbox.filled   = Colours::transparentBlack;
	chatbox.position = {5, APP_SCREEN_SIZE_H - 30};
	chatbox.size     = {APP_SCREEN_SIZE_W - 10, app->text.GetTextSize("A", 1.0).y + 2};
	chatScroll       = 0;

	player.inventory.Hotbar()[0] = {
		false, 3, 1
	};
	player.inventory.Hotbar()[1] = {
		false, 1, 1
	};
	player.inventory.Hotbar()[2] = {
		false, 4, 1
	};
	player.inventory.Hotbar()[3] = {
		false, 5, 1
	};

	inventoryScreen.inventory = &player.inventory;
	inventoryScreen.parent    = this;
}

void Game::SpawnPlayer() {
	player.position.x = level.size.x / 2;
	player.position.y = level.size.y / 2;
}

void Game::Deinit() {
	level.Destroy();
}

void Game::Update(AppState& state) {
	switch (gameState) {
		case GameState::Running: {
			GetHighlightedBlock();
			UpdateCamera();
			particles.UpdateParticles();
			break;
		}
		case GameState::Paused: {
			pauseMenu.Update(state, *this);
			break;
		}
		case GameState::InChat: {
			break;
		}
		case GameState::Inventory: {
		    inventoryScreen.Update();
		}
	}
}

void Game::HandleEvent(SDL_Event& event) {
	switch (gameState) {
		case GameState::Paused: {
			pauseMenu.HandleEvent(event);
			break;
		}
		case GameState::Running: {
			switch (event.type) {
				case SDL_MOUSEMOTION: {
					mousePosition.x = event.motion.x;
					mousePosition.y = event.motion.y;
					break;
				}
				case SDL_MOUSEBUTTONDOWN: {
					switch (event.button.button) {
						case SDL_BUTTON_LEFT: {
							DeleteBlock();
							mouseDown = true;
							break;
						}
						case SDL_BUTTON_RIGHT: {
							PlaceBlock();
							break;
						}
					}
					break;
				}
				case SDL_MOUSEBUTTONUP: {
					mouseDown =
						event.button.button == SDL_BUTTON_LEFT? true : mouseDown;
					break;
				}
				case SDL_MOUSEWHEEL: {
					if (event.wheel.y > 0) { // up
						if (player.inventory.hotbarSelection == 0) {
							player.inventory.hotbarSelection =
								player.inventory.Hotbar().size() - 1;
						}
						else {
							-- player.inventory.hotbarSelection;
						}
					}
					else if (event.wheel.y < 0) { // down
						player.inventory.hotbarSelection =
							(player.inventory.hotbarSelection + 1) %
							player.inventory.Hotbar().size();
					}
					break;
				}
				case SDL_KEYUP: {
				    switch (event.key.keysym.scancode) {
				        case SDL_SCANCODE_ESCAPE: {
				            gameState = GameState::Paused;
				            SDL_ShowCursor(SDL_ENABLE);
				            break;
				        }
				        case SDL_SCANCODE_T: {
				        	gameState       = GameState::InChat;
				        	chatbox.focused = true;
				        	break;
				        }
				        case SDL_SCANCODE_E: {
				        	gameState = GameState::Inventory;
				        	SDL_ShowCursor(SDL_ENABLE);
				        	break;
				        }
				        default: break;
				    }
				    break;
				}
			}
			break;
		}
		case GameState::InChat: {
			switch (event.type) {
				case SDL_KEYUP: {
					if (
						(event.type == SDL_KEYUP) &&
						(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					) {
						chatbox.Reset();
						gameState     = GameState::Running;
						break;
					}
					break;
				}
				case SDL_KEYDOWN:
				case SDL_TEXTINPUT: {
					chatbox.HandleEvent(event);
					if (!chatbox.focused) {
						gameState     = GameState::Running;
						if (chatbox.input == "") {}
						else if (Chat::IsCommand(chatbox.input)) {
							auto cmdParts = Chat::ParseCommand(chatbox.input);
							auto command  = cmdParts[0];
							std::vector <std::string> args = cmdParts;
							
							args.erase(args.begin());
							commands.RunCommand(command, args);
						}
						else {
							chat.insert(chat.begin(), {SDL_GetTicks(), chatbox.input});
						}
						chatbox.Reset();
					}
					break;
				}
				case SDL_MOUSEWHEEL: {
					if (event.wheel.y > 0) { // up
						if (chatScroll + GAME_CHAT_HEIGHT < chat.size()) {
							++ chatScroll;
						}
					}
					else if (event.wheel.y < 0) { // down
						if (chatScroll != 0) {
							-- chatScroll;
						}
					}
					break;
				}
			}
			break;
		}
		case GameState::Inventory: {
		    inventoryScreen.HandleEvent(event);
		    break;
		}
	}
}

void Game::UpdateCamera() {
	camera.x = player.position.x - (APP_SCREEN_SIZE_W / 2 / GAME_BLOCK_SIZE);
	camera.y = player.position.y - (APP_SCREEN_SIZE_H / 2 / GAME_BLOCK_SIZE);
}

void Game::HandleInput(const Uint8* keystate, double delta) {
	if (gameState != GameState::Running) {
		return;
	}
	double multiplier =
		keystate[SDL_SCANCODE_LSHIFT]?
			GAME_PLAYER_FAST_SPEED : keystate[SDL_SCANCODE_RSHIFT]?
				GAME_PLAYER_FAST_SPEED : GAME_PLAYER_SPEED;

    player.Reset();
	if (keystate[SDL_SCANCODE_W]) {
		player.GoUp(delta, multiplier, level, blockdefs);
		player.EdgeCollision(level);
		UpdateCamera();
	}
	if (keystate[SDL_SCANCODE_S]) {
		player.GoDown(delta, multiplier, level, blockdefs);
		player.EdgeCollision(level);
		UpdateCamera();
	}
	if (keystate[SDL_SCANCODE_A]) {
		player.GoLeft(delta, multiplier, level, blockdefs);
		player.EdgeCollision(level);
		UpdateCamera();
	}
	if (keystate[SDL_SCANCODE_D]) {
		player.GoRight(delta, multiplier, level, blockdefs);
		player.EdgeCollision(level);
		UpdateCamera();
	}
	player.Update();

	if (keystate[SDL_SCANCODE_1]) player.inventory.hotbarSelection = 0;
	if (keystate[SDL_SCANCODE_2]) player.inventory.hotbarSelection = 1;
	if (keystate[SDL_SCANCODE_3]) player.inventory.hotbarSelection = 2;
	if (keystate[SDL_SCANCODE_4]) player.inventory.hotbarSelection = 3;
	if (keystate[SDL_SCANCODE_5]) player.inventory.hotbarSelection = 4;
	if (keystate[SDL_SCANCODE_6]) player.inventory.hotbarSelection = 5;
	if (keystate[SDL_SCANCODE_7]) player.inventory.hotbarSelection = 6;
	if (keystate[SDL_SCANCODE_8]) player.inventory.hotbarSelection = 7;
	if (keystate[SDL_SCANCODE_9]) player.inventory.hotbarSelection = 8;
}

void Game::Render() {
	// render level
	{
		Vec2 max;
		max.x = camera.x + (APP_SCREEN_SIZE_W / GAME_BLOCK_SIZE) + 2;
		max.y = camera.y + (APP_SCREEN_SIZE_H / GAME_BLOCK_SIZE) + 2;
		
		Vec2 start;
		start.x = camera.x > 0? camera.x : 0;
		start.y = camera.y > 0? camera.y : 0;

		for (
			ssize_t i = start.y; (i < max.y) && (i < level.size.y); ++i
		) {
			for (
				ssize_t j = start.x; (j < max.x) && (j < level.size.x); 
				++j
			) { 
				Vec2 block;
				block.x = (j * GAME_BLOCK_SIZE) - (camera.x * GAME_BLOCK_SIZE);
				block.y = (i * GAME_BLOCK_SIZE) - (camera.y * GAME_BLOCK_SIZE);
				
				if (blockdefs.defs[level.layers[0].back[i][j]].type != BlockType::Gas) {
					app->gameTextures.RenderTile(
						app->video.renderer,
						blockdefs.defs[level.layers[0].back[i][j]].textureID,
						block
					);
				}
			}
		}

		for (
			ssize_t i = start.y; (i < max.y) && (i < level.size.y); ++i
		) {
			for (
				ssize_t j = start.x; (j < max.x) && (j < level.size.x); ++j
			) {
				Vec2 block;
				block.x = (j * GAME_BLOCK_SIZE) - (camera.x * GAME_BLOCK_SIZE);
				block.y = (i * GAME_BLOCK_SIZE) - (camera.y * GAME_BLOCK_SIZE);
			
				if (blockdefs.defs[level.layers[0].front[i][j]].type != BlockType::Gas) {
					// render shadow
					SDL_SetRenderDrawColor(app->video.renderer, 0, 0, 0, 127);
					SDL_Rect shadow = {
						block.x + GAME_SHADOW_OFFSET, block.y + GAME_SHADOW_OFFSET,
						GAME_BLOCK_SIZE, GAME_BLOCK_SIZE
					};
					SDL_RenderFillRect(app->video.renderer, &shadow);
					if (
						(j == 0) ||
						(
							blockdefs.defs[level.layers[0].front[i][j - 1]].type ==
							BlockType::Gas
						)
					) {
						app->video.DrawTriangle(
							{(float) block.x, (float) block.y + GAME_BLOCK_SIZE},
							{
								(float) block.x + GAME_SHADOW_OFFSET,
								(float) block.y + GAME_BLOCK_SIZE
							},
							{
								(float) block.x + GAME_SHADOW_OFFSET,
								(float) block.y + GAME_BLOCK_SIZE + GAME_SHADOW_OFFSET
							},
							Colours::transparentBlack
						);
					}
					if (
						(i == 0) ||
						(
							blockdefs.defs[level.layers[0].front[i - 1][j]].type ==
							BlockType::Gas
						)
					) {
						app->video.DrawTriangle(
							{(float) block.x + GAME_BLOCK_SIZE, (float) block.y},
							{
								(float) block.x + GAME_BLOCK_SIZE,
								(float) block.y + GAME_SHADOW_OFFSET
							},
							{
								(float) block.x + GAME_BLOCK_SIZE + GAME_SHADOW_OFFSET,
								(float) block.y + GAME_SHADOW_OFFSET
							},
							Colours::transparentBlack
						);
					}
					// render texture
					app->gameTextures.RenderTile(
						app->video.renderer,
						blockdefs.defs[level.layers[0].front[i][j]].textureID,
						block
					);

					// render borders
					SDL_SetRenderDrawColor(app->video.renderer, 255, 255, 255, 255);
					if (
						(j > 0) &&
						level.ValidBlock({(int) j - 1, (int) i}) &&
						(blockdefs.defs[level.layers[0].front[i][j - 1]].type !=
						BlockType::Solid)
					) {
						SDL_RenderDrawLine(
							app->video.renderer,
							block.x, block.y, block.x, block.y + GAME_BLOCK_SIZE - 1
						);
					}
					if (
						(j < level.size.x) &&
						level.ValidBlock({(int) j + 1, (int) i}) &&
						(blockdefs.defs[level.layers[0].front[i][j + 1]].type !=
						BlockType::Solid)
					) {
						SDL_RenderDrawLine(
							app->video.renderer,
							block.x + GAME_BLOCK_SIZE - 1, block.y,
							block.x + GAME_BLOCK_SIZE - 1, block.y + GAME_BLOCK_SIZE - 1
						);
					}
					if (
						(i > 0) &&
						level.ValidBlock({(int) j, (int) i - 1}) &&
						(blockdefs.defs[level.layers[0].front[i - 1][j]].type !=
						BlockType::Solid)
					) {
						SDL_RenderDrawLine(
							app->video.renderer,
							block.x, block.y, block.x + GAME_BLOCK_SIZE - 1, block.y
						);
					}
					if (
						(i < level.size.y) &&
						level.ValidBlock({(int) j, (int) i + 1}) &&
						(blockdefs.defs[level.layers[0].front[i + 1][j]].type !=
						BlockType::Solid)
					) {
						SDL_RenderDrawLine(
							app->video.renderer,
							block.x, block.y + GAME_BLOCK_SIZE - 1,
							block.x + GAME_BLOCK_SIZE - 1, block.y + GAME_BLOCK_SIZE - 1
						);
					}
				}

				if (
					blockHighlighted &&
					(highlightedBlock.x == (size_t) j) &&
					(highlightedBlock.y == (size_t) i)
				) {
					SDL_SetRenderDrawColor(app->video.renderer, 204, 66, 94, 255);
					SDL_Rect rect;
					rect.x = block.x;
					rect.y = block.y;
					rect.w = GAME_BLOCK_SIZE;
					rect.h = GAME_BLOCK_SIZE;
					SDL_RenderDrawRect(app->video.renderer, &rect);
				}
			}
		}
	}

	// render particles
	particles.Render(app->video, camera);

	// render player
	app->gameTextures.RenderTile(
		app->video.renderer, player.GetTextureID(), 
		{
			(int32_t) round(player.position.x - camera.x) * GAME_BLOCK_SIZE,
			(int32_t) round(player.position.y - camera.y) * GAME_BLOCK_SIZE
		}
		// rounds the player position to prevent the player appearing to stutter in
		// movement
	);

	// render inventory
	{
		size_t startX =
			(APP_SCREEN_SIZE_W / 2) -
			((GAME_BLOCK_SIZE * player.inventory.Hotbar().size()) / 2);
		size_t startY = APP_SCREEN_SIZE_H - (GAME_BLOCK_SIZE + 6);

		{ // background
			SDL_SetRenderDrawColor(app->video.renderer, 255, 255, 255, 127);
			SDL_Rect background;
			background.x = startX;
			background.y = startY;
			background.w = player.inventory.Hotbar().size() * GAME_BLOCK_SIZE;
			background.h = GAME_BLOCK_SIZE;
			SDL_RenderFillRect(app->video.renderer, &background);
		}

		for (size_t i = 0; i < player.inventory.Hotbar().size(); ++i) {
			Vec2 pos = {(int32_t) (startX + (i * GAME_BLOCK_SIZE)), (int32_t) startY};
			if (
				(blockdefs.defs[player.inventory.Hotbar()[i].block].type
				!= BlockType::Gas) &&
				(!player.inventory.Hotbar()[i].empty)
			) {
				app->gameTextures.RenderTile(
					app->video.renderer,
					blockdefs.defs[player.inventory.Hotbar()[i].block].textureID,
					pos
				);
			}
			if (i == player.inventory.hotbarSelection) {
				SDL_Rect box;
				box.x = pos.x;
				box.y = pos.y;
				box.w = GAME_BLOCK_SIZE;
				box.h = GAME_BLOCK_SIZE;
				SDL_SetRenderDrawColor(app->video.renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(app->video.renderer, &box);
			}
		}

		SDL_SetRenderDrawColor(app->video.renderer, 222, 222, 222, 127);
		SDL_Rect outline;
		outline.x = startX - 1;
		outline.y = startY - 1;
		outline.w = GAME_BLOCK_SIZE * player.inventory.Hotbar().size() + 2;
		outline.h = GAME_BLOCK_SIZE + 2;
		SDL_RenderDrawRect(app->video.renderer, &outline);
		-- outline.x;
		-- outline.y;
		outline.w += 2;
		outline.h += 2;
		SDL_SetRenderDrawColor(app->video.renderer, 31, 16, 42, 127);
		SDL_RenderDrawRect(app->video.renderer, &outline);
	}

	// render paused menu
	if (gameState == GameState::Paused) {
		pauseMenu.Render(app->video.renderer, app->text);
		return;
	}

	// render chat
	{
		int  letterHeight = app->text.GetTextSize("A", 1.0).y;
		Vec2 chatPosition = {chatbox.position.x, chatbox.position.y - letterHeight - 1};
		Vec2 textPosition = {chatbox.position.x, chatPosition.y};
		for (size_t i = chatScroll; i < chat.size(); ++i, textPosition.y -= letterHeight) {
			if (i > GAME_CHAT_HEIGHT - 1) {
				break;
			}
			if (
				(gameState == GameState::InChat) ||
				!SDL_TICKS_PASSED(SDL_GetTicks(), chat[i].time + 5000)
			) {
				app->text.RenderText(
					app->video.renderer, chat[i].content, textPosition, 1.0, true
				);
			}
		}
	}
	
	// render UI
	app->text.RenderText(
		app->video.renderer, "FPS: " + std::to_string(app->fps),
		{5, 5}, 1, true
	);
	app->text.RenderText(
		app->video.renderer,
		"Pos: (" + std::to_string(player.position.x) + ", " +
			std::to_string(player.position.y) + ")",
		{5, 25}, 1, true
	);

	if (gameState == GameState::InChat) {
		chatbox.Render(app->video.renderer, app->text);
		return;
	}
	if (gameState == GameState::Inventory) {
	    inventoryScreen.Render(app->video.renderer, app->text);
	    return;
	}

	// render cursor
	SDL_SetRenderDrawColor(app->video.renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(
		app->video.renderer, mousePosition.x, mousePosition.y - 2,
		mousePosition.x, mousePosition.y - 4
	);
	SDL_RenderDrawLine(
		app->video.renderer, mousePosition.x, mousePosition.y + 2,
		mousePosition.x, mousePosition.y + 4
	);
	SDL_RenderDrawLine(
		app->video.renderer, mousePosition.x - 2, mousePosition.y,
		mousePosition.x - 4, mousePosition.y
	);
	SDL_RenderDrawLine(
		app->video.renderer, mousePosition.x + 2, mousePosition.y,
		mousePosition.x + 4, mousePosition.y
	);
}

void Game::GetHighlightedBlock() {
	blockHighlighted = false;

	Vec2 max;
	max.x = camera.x + (APP_SCREEN_SIZE_W / GAME_BLOCK_SIZE) + 2;
	max.y = camera.y + (APP_SCREEN_SIZE_H / GAME_BLOCK_SIZE) + 2;
	
	Vec2 start;
	start.x = (camera.x / GAME_BLOCK_SIZE) > 0? camera.x / GAME_BLOCK_SIZE : 0;
	start.y = (camera.y / GAME_BLOCK_SIZE) > 0? camera.y / GAME_BLOCK_SIZE : 0;

	for (
		ssize_t i = start.y / GAME_BLOCK_SIZE; (i < max.y) && (i < level.size.y); ++i
	) {
		for (
			ssize_t j = start.x / GAME_BLOCK_SIZE; (j < max.x) && (j < level.size.x); 
			++j
		) {
			Vec2 block;
			block.x = (j * GAME_BLOCK_SIZE) - (camera.x * GAME_BLOCK_SIZE);
			block.y = (i * GAME_BLOCK_SIZE) - (camera.y * GAME_BLOCK_SIZE);

			if (
				(mousePosition.x >= block.x) &&
				(mousePosition.y >= block.y) &&
				(mousePosition.x < block.x + GAME_BLOCK_SIZE) &&
				(mousePosition.y < block.y + GAME_BLOCK_SIZE)
			) {
				if (
					(player.position.x - j > 5) ||
					(player.position.x - j < -5) ||
					(player.position.y - i > 5) ||
					(player.position.y - i < -5)
				) {
					return;
				}
				blockHighlighted = true;
				highlightedBlock = {(size_t) j, (size_t) i};

				if (
					(
						((size_t) floor(player.position.x) == highlightedBlock.x) &&
						((size_t) floor(player.position.y) == highlightedBlock.y)
					) ||
					(
						((size_t) ceil(player.position.x) == highlightedBlock.x) &&
						((size_t) floor(player.position.y) == highlightedBlock.y)
					) ||
					(
						((size_t) floor(player.position.x) == highlightedBlock.x) &&
						((size_t) ceil(player.position.y) == highlightedBlock.y)
					) ||
					(
						((size_t) ceil(player.position.x) == highlightedBlock.x) &&
						((size_t) ceil(player.position.y) == highlightedBlock.y)
					)
				) {
					blockHighlighted = false;
				}
			}
		}
	}
}

void Game::PlaceBlock() {
	if (!blockHighlighted) {
		return;
	}
	
	size_t y = highlightedBlock.y;
	size_t x = highlightedBlock.x;
	if (
		blockdefs.defs[level.layers[0].back[y][x]].type == BlockType::Gas
	) {
		level.layers[0].back[y][x] = player.inventory.Hotbar()[
			player.inventory.hotbarSelection
		].block;
		return;
	}

	if (
		blockdefs.defs[level.layers[0].front[y][x]].type == BlockType::Gas
	) {
		level.layers[0].front[y][x] = player.inventory.Hotbar()[
			player.inventory.hotbarSelection
		].block;
	}
}

void Game::DeleteBlock() {
	if (!blockHighlighted) {
		return;
	}
	
	size_t    y = highlightedBlock.y;
	size_t    x = highlightedBlock.x;
	blockID_t id;
	bool      createParticles = false;
	if (
		blockdefs.defs[level.layers[0].front[y][x]].type != BlockType::Gas
	) {
		id = level.layers[0].front[y][x];
		level.layers[0].front[y][x] = 0;
		createParticles             = true;
	}
	else if (
		blockdefs.defs[level.layers[0].back[y][x]].type != BlockType::Gas
	) {
		id = level.layers[0].back[y][x];
		level.layers[0].back[y][x] = 0;
		createParticles            = true;
	}

	if (createParticles) {
		for (int i = 0; i < Util::RandomRange(15, 30); ++i) {
			particles.NewParticle(
				blockdefs.defs[id].textureID, {(uint32_t) x, (uint32_t) y}
			);
		}
	}
}

void Game::AddToChat(std::string message) {
	chat.insert(chat.begin(), {SDL_GetTicks(), message});
}