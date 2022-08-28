#ifndef YCRAFT_GAME_HH
#define YCRAFT_GAME_HH

#include "_components.hh"
#include "blockdefs.hh"
#include "types.hh"
#include "level.hh"
#include "player.hh"

class App;

class Game {
	public:
		// variables
		Blockdefs blockdefs;
		FVec2     camera; // unit: blocks
		Level     level;
		Player    player; // unit: blocks
		Vec2      mousePosition;
		WVec2     highlightedBlock;
		bool      blockHighlighted;

		// functions
		Game() {}
		void Init();
		void Update();
		void HandleEvent(SDL_Event& event);
		void UpdateCamera();
		void HandleInput(const Uint8* keystate, double delta);
		void Render(App& app);
		void GetHighlightedBlock();
		void PlaceBlock();
		void DeleteBlock();
};

#endif
