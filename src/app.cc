#include "app.hh"
#include "util.hh"
#include "constants.hh"
#include "fs.hh"
#include "chat.hh"

App::App():
	run(true),
	gameFolder(Util::DirName(Util::GetExecutableLocation()))
{
	Util::Log("Welcome to " APP_NAME);

	srand(time(nullptr));

	if (Util::GetExecutableLocation() == "") {
		Util::Error(APP_NAME " can't run on your system");
	}
	
	deltaLast  = 0;
	deltaNow   = SDL_GetPerformanceCounter();
	state      = AppState::TitleScreen;

	Util::Log("Found game folder: %s", gameFolder.c_str());

	
	curl.Init();
	SetupGameFiles();
	DownloadAssets();
	Util::Log("Set up game files");
	
	video.Init();
	text.Init(gameFolder + "/font.ttf");
	image.Init();
	audio.Init();
	audio.LoadMusic(gameFolder + "/music");

	InitCommands(this);

	settings.Load(gameFolder);
	UpdateSettings();
	settingsMenu.settings            = &settings;
	texturePackSelectorMenu.settings = &settings;
	texturePackSelectorMenu.Init(gameFolder);
	worldsMenu.Init(gameFolder);

	game.level.worldsPath = gameFolder + "/maps";
	game.app              = this;
	
/*
	game.Init();

	gameTextures.Init(
		video.renderer, gameFolder + "/texpacks/default.png", GAME_BLOCK_SIZE
	);

	SDL_ShowCursor(SDL_DISABLE);
*/
	Util::Log("Ready");
}

App::~App() {
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}

	video.Free();
	text.Free();
	image.Free();
	curl.Free();

	Util::Log("Goodbye");
}

void App::Update() {
	// play music if none playing
	if (!Mix_PlayingMusic() && settings.settings["playMusic"] == "true") {
		audio.LoadMusic(gameFolder + "/music");
	}

	// get delta time
	deltaLast = deltaNow;
	deltaNow  = SDL_GetPerformanceCounter();
	deltaTime = (double) ((deltaNow - deltaLast) * 1000 /
		(double) SDL_GetPerformanceFrequency());
	// https://gamedev.stackexchange.com/questions/110825/how-to-calculate-delta-time-with-sdl

	// calculate fps
	if (SDL_GetPerformanceCounter() % 10 == 0) {
		fps = (int) (1000 / deltaTime);
	}

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: {
				run = false;
				break;
			}
			default: {
				switch (state) {
					case AppState::InGame: {
						game.HandleEvent(event);
						break;
					}
					case AppState::TitleScreen: {
						titleScreen.HandleEvent(event);
						break;
					}
					case AppState::WorldMenu: {
						worldsMenu.HandleEvent(event);
						break;
					}
					case AppState::SettingsMenu: {
						settingsMenu.HandleEvent(event);
						break;
					}
					case AppState::NewWorldMenu: {
						newWorldMenu.HandleEvent(event);
						break;
					}
					case AppState::TexturePackSelectorMenu: {
						texturePackSelectorMenu.HandleEvent(event);
						break;
					}
					case AppState::CreditsScreen: {
						creditsScreen.HandleEvent(event);
					}
				}
				break;
			}
		}
	}

	switch (state) {
		case AppState::InGame: {
			game.Update(state);
		
			const Uint8* keystate = SDL_GetKeyboardState(nullptr);
			game.HandleInput(keystate, deltaTime);
			break;			
		}
		case AppState::TitleScreen: {
			if (!titleScreen.Update(state)) {
				run = false;
			}
			if (state == AppState::SettingsMenu) {
				settingsMenu.Init();
			}
			break;
		}
		case AppState::WorldMenu: {
			worldsMenu.Update(state);

			if (state == AppState::InGame) {
				game.Init({0, 0}, false);
				game.level.LoadLevel(
					gameFolder + "/maps/" +
					worldsMenu.worlds.options[worldsMenu.worlds.set]
				);
				game.level.name = worldsMenu.worlds.options[worldsMenu.worlds.set];
				game.SpawnPlayer();
				gameTextures.Init(
					video.renderer,
					gameFolder + "/texpacks/" + settings.settings["texturePack"],
					GAME_BLOCK_SIZE
				);

				SDL_ShowCursor(SDL_DISABLE);
			}
			break;
		}
		case AppState::SettingsMenu: {
			if (settingsMenu.Update(state)) {
				UpdateSettings();
			}
			break;
		}
		case AppState::NewWorldMenu: {
			newWorldMenu.Update(state);
			if (state == AppState::InGame) {
				uint32_t size = pow(2, (newWorldMenu.worldSizeSelection.set * 2) + 6);
				game.Init({size, size}, true);
				game.level.name = newWorldMenu.worldName.input;
				if (game.level.name == "") {
					game.level.name = "My World";
				}

				gameTextures.Init(
					video.renderer,
					gameFolder + "/texpacks/" + settings.settings["texturePack"],
					GAME_BLOCK_SIZE
				);

				SDL_ShowCursor(SDL_DISABLE);
			}
			break;
		}
		case AppState::TexturePackSelectorMenu: {
			texturePackSelectorMenu.Update(state);

			if (state != AppState::TexturePackSelectorMenu) {
				std::string path =
					texturePackSelectorMenu.options.options[
						texturePackSelectorMenu.options.set
					];

				if (path.empty()) {
					break;
				}
			
				settings.settings["texturePack"] = path;
			}
			break;
		}
		case AppState::CreditsScreen: {
			creditsScreen.Update(state);
			break;
		}
	}

	Render();
}

void App::Render() {
	SDL_SetRenderDrawColor(video.renderer, 0, 0, 25, 255);
	SDL_RenderClear(video.renderer);

	switch (state) {
		case AppState::InGame: {
			game.Render();
			break;
		}
		case AppState::TitleScreen: {
			titleScreen.Render(video.renderer, text);
			break;
		}
		case AppState::WorldMenu: {
			worldsMenu.Render(video.renderer, text);
			break;
		}
		case AppState::SettingsMenu: {
			settingsMenu.Render(video.renderer, text);
			break;
		}
		case AppState::NewWorldMenu: {
			newWorldMenu.Render(video.renderer, text);
			break;
		}
		case AppState::TexturePackSelectorMenu: {
			texturePackSelectorMenu.Render(video.renderer, text);
			break;
		}
		case AppState::CreditsScreen: {
			creditsScreen.Render(video.renderer, text);
			break;
		}
	}

	SDL_RenderPresent(video.renderer);
}

void App::UpdateSettings() {
	SDL_SetWindowFullscreen(
		video.window,
		settings.settings["fullscreen"] == "true"? SDL_WINDOW_FULLSCREEN_DESKTOP : 0
	);
	audio.enabled = settings.settings["playMusic"] == "true";
	if (!audio.enabled && Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}
}

void App::SetupGameFiles() {
	std::vector <std::string> requiredDirectories = {
		"texpacks", "maps", "music"
	};
	for (auto& dir : requiredDirectories) {
		if (!FS::Directory::Exists(gameFolder + "/" + dir)) {
			FS::Directory::Create(gameFolder + "/" + dir);
		}
	}
}

void App::DownloadAssets() {
	std::vector <std::string> requiredFiles = {
		"font.ttf", "texpacks/default.png",
		"music/098761584987960161196106.mp3",
		"music/Misery_Rope_Here.mp3",
		"music/Nevertheless_Life_Is_Beautiful.mp3"
	};
	
	bool needsDownload = false;
	for (auto& file : requiredFiles) {
		if (!FS::File::Exists(gameFolder + "/" + file)) {
			needsDownload = true;
		}
	}
	if (!needsDownload) {
		return;
	}

	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_INFORMATION, "Information",
		"Some assets are going to be downloaded from the internet", nullptr
	);

	for (auto& file : requiredFiles) {
		std::string path = gameFolder + "/" + file;
		if (!FS::File::Exists(path)) {
			curl.Download(
				std::string(APP_RESOURCES_URL) + file,
				gameFolder + "/" + file
			);
		}
	}
}
