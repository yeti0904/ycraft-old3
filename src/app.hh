#pragma once
#include "_components.hh"
#include "video.hh"
#include "text.hh"
#include "image.hh"
#include "tiles.hh"
#include "game.hh"
#include "titleScreen.hh"

enum class AppState {
	InGame = 0,
	TitleScreen
};

class App {
	public:
		// variables
		bool                      run;
		VideoComponents           video;
		TextComponents            text;
		ImageComponents           image;
		std::string               gameFolder;
		TileSheet                 gameTextures;
		std::vector <std::string> credits;
		Game                      game;
		Uint64                    deltaNow;
		Uint64                    deltaLast;
		double                    deltaTime;
		uint16_t                  fps;
		AppState                  state;

		Menus::TitleScreen titleScreen;

		// functions
		App();
		~App();
		void Update();
		void Render();
};
