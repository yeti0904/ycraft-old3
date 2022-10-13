#ifndef YCRAFT_AUDIO_HH
#define YCRAFT_AUDIO_HH

#include "_components.hh"

class AudioComponents {
	public:
		Mix_Music*                music;
		std::vector <std::string> musicFiles;

		AudioComponents();
		~AudioComponents();
		void Init();
		void LoadMusic(std::string directory);
		void FreeMusic();
};

#endif