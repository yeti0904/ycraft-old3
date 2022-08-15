#include "app.hh"
#include "util.hh"
#include "constants.hh"

App::App() {
	Util::Log("Welcome to " APP_NAME);

	if (Util::GetExecutableLocation() == "") {
		fprintf(stderr, APP_NAME " can't run on your system\n");
		exit(EXIT_FAILURE);
	}

	run        = true;
	gameFolder = Util::DirName(Util::GetExecutableLocation());
	deltaLast  = 0;
	deltaNow   = SDL_GetPerformanceCounter();

	credits = {
		"programming: MESYETI",
		"art: MESYETI, LordOfTrident",
		"font: Zeh Fernando"
	};

	Util::Log("Found game folder: %s", gameFolder.c_str());
	
	video.Init();
	text.Init(gameFolder + "/font.ttf");
	image.Init();

	game.Init();

	gameTextures.Init(
		video.renderer, gameFolder + "/texpacks/default.png", GAME_BLOCK_SIZE
	);

	SDL_ShowCursor(SDL_DISABLE);

	Util::Log("Ready");
}

App::~App() {
	video.Free();
	text.Free();
	image.Free();

	Util::Log("Goodbye");
}

void App::Update() {
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
				game.HandleEvent(event);
				break;
			}
		}
	}

	game.Update();

	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	game.HandleInput(keystate, deltaTime);

	Render();
}

void App::Render() {
	SDL_SetRenderDrawColor(video.renderer, 0, 0, 25, 255);
	SDL_RenderClear(video.renderer);

	game.Render(*this);	

	SDL_RenderPresent(video.renderer);
}
