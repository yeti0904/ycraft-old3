#ifndef YCRAFT_SETTINGS_HH
#define YCRAFT_SETTINGS_HH

#include "_components.hh"
#include "properties.hh"

class SettingsManager {
	public:
		// variables
		Properties  settings;
		std::string settingsPath;

		SettingsManager() {}
		void Load(std::string gamePath);
		void Write();
};

#endif
