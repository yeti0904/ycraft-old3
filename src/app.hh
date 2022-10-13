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
#include "newWorldMenu.hh"
#include "texturePackSelectorMenu.hh"
#include "curl.hh"
#include "audio.hh"
#include "creditsScreen.hh"

enum class AppState {
	InGame = 0,
	TitleScreen,
	WorldMenu,
	SettingsMenu,
	NewWorldMenu,
	TexturePackSelectorMenu,
	CreditsScreen
};

class App {
	public:
		// variables
		bool            run;
		std::string     gameFolder;
		VideoComponents video;
		TextComponents  text;
		ImageComponents image;
		CurlComponents  curl;
		AudioComponents audio;
		TileSheet       gameTextures;
		Game            game;
		Uint64          deltaNow;
		Uint64          deltaLast;
		double          deltaTime;
		uint16_t        fps;
		AppState        state;
		SettingsManager settings;

		Menus::TitleScreen         titleScreen;
		Menus::WorldsMenu          worldsMenu;
		Menus::SettingsMenu        settingsMenu;
		Menus::NewWorldMenu        newWorldMenu;
		Menus::TexturePackSelector texturePackSelectorMenu;
		Menus::CreditsScreen       creditsScreen;

		// functions
		App();
		~App();
		void Update();
		void Render();

		void UpdateSettings();
		void SetupGameFiles();
		void DownloadAssets();
};

#endif
