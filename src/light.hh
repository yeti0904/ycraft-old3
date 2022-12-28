#ifndef YCRAFT_LIGHT_HH
#define YCRAFT_LIGHT_HH

#include "_components.hh"
#include "types.hh"

struct LevelLayer;

typedef uint8_t lightLevel_t;

struct LightSource {
	Vec2         position;
	lightLevel_t strength;
};

class LevelLight {
	public:
		// variables
		lightLevel_t              globalLightLevel;
		std::vector <LightSource> lightSources;

		// functions
		LevelLight();
		static lightLevel_t LightMax();
		lightLevel_t        CalculateLightLevel(Vec2 pos);
		void                AddLightSource(Vec2 pos, lightLevel_t strength);
		void                DestroyLightSource(Vec2 pos);
};

#endif
