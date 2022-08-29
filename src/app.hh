#ifndef YCRAFT_APP_HH
#define YCRAFT_APP_HH

#include "_components.hh"
#include "video.hh"
#include "text.hh"
#include "image.hh"
#include "tiles.hh"
#include "game.hh"
#include "titleScreen.hh"
#include "worldMenu.hh"
#include "settingsMenu.hh"
#include "settings.hh"

enum class AppState {
	InGame = 0,
	TitleScreen,
	WorldMenu,
	SettingsMenu
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
		SettingsManager           settings;

		Menus::TitleScreen  titleScreen;
		Menus::WorldsMenu   worldsMenu;
		Menus::SettingsMenu settingsMenu;

		// functions
		App();
		~App();
		void Update();
		void Render();

		void UpdateSettings();
};

#endif
