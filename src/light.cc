#include "light.hh"
#include "util.hh"

LevelLight::LevelLight():
	globalLightLevel(10)
{
	
}

lightLevel_t LevelLight::LightMax() {
	return 255;
}

lightLevel_t LevelLight::CalculateLightLevel(Vec2 pos) {
	lightLevel_t ret = globalLightLevel;

	for (auto& source : lightSources) {
		int  addOn =  Util::Distance(pos, source.position);
		addOn      *= source.strength;

		ret = std::max((int) ret + addOn, (int) LightMax());
	}

	return ret;
}

void LevelLight::AddLightSource(Vec2 pos, lightLevel_t strength) {
	lightSources.push_back({pos, strength});
}

void LevelLight::DestroyLightSource(Vec2 pos) {
	for (size_t i = 0; i < lightSources.size(); ++i) {
		if (
			(lightSources[i].position.x == pos.x) &&
			(lightSources[i].position.y == pos.y)
		) {
			lightSources.erase(lightSources.begin() + i);
			return;
		}
	}
}
