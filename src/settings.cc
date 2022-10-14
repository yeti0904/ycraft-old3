#include "settings.hh"
#include "fs.hh"

void SettingsManager::Load(std::string gamePath) {
	settingsPath = gamePath + "/settings.properties";

	if (!FS::File::Exists(settingsPath)) {
		FS::File::Write(
			settingsPath,
			"fullscreen = false\n"
			"texturePack = default.png\n"
			"playMusic = true"
		);
	}
	settings.Parse(FS::File::Read(settingsPath));
}

void SettingsManager::Write() {
	FS::File::Write(settingsPath, settings.Stringify());
}
