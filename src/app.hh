#pragma once
#include "_components.hh"
#include "video.hh"
#include "text.hh"
#include "image.hh"
#include "tiles.hh"
#include "game.hh"

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

		// functions
		App();
		~App();
		void Update();
		void Render();
};
