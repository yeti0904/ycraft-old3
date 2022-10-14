#include "audio.hh"
#include "util.hh"

AudioComponents::AudioComponents():
	music(nullptr)
{
	
}

AudioComponents::~AudioComponents() {
	if (music != nullptr) {
		Mix_FreeMusic(music);
	}
}

void AudioComponents::Init() {
	int initFlags = MIX_INIT_MP3;
	if (Mix_Init(initFlags) != initFlags) {
		Util::Error("Failed to initialise SDL_Mixer: %s", Mix_GetError());
	}
	if (
		Mix_OpenAudio(
			MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096
		) != 0
	) {
		Util::Error("Failed to open audio device: %s", Mix_GetError());
	}
	Mix_VolumeMusic(100);
	Mix_SetMusicCMD(SDL_getenv("MUSIC_CMD"));
}

void AudioComponents::LoadMusic(std::string directory) {
	if (!enabled) {
		return;
	}

	auto files = Util::GetFilesOfType(directory, ".mp3");

	if (files.empty()) {
		return;
	}

	auto index  = Util::RandomRange(0, files.size() - 1);
	auto chosen = files[index];
	music = Mix_LoadMUS((chosen).c_str());
	if (music == nullptr) {
		Util::Error("Failed to open music %s: %s", chosen.c_str(), Mix_GetError());
	}
	if (Mix_PlayMusic(music, 0) != 0) {
		Util::Error("Failed to play music %s: %s", chosen.c_str(), Mix_GetError());
	}
}

void AudioComponents::FreeMusic() {
	Mix_FreeMusic(music);
	music = nullptr;
}