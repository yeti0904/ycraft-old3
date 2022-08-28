#ifndef YCRAFT_LIGHT_HH
#define YCRAFT_LIGHT_HH

#include "_components.hh"
#include "types.hh"

struct LevelLayer;

typedef uint8_t lightLevel_t;

class LevelLight {
	public:
		// variables
		lightLevel_t                             globalLightLevel;
		std::vector <std::vector <lightLevel_t>> light;
};

#endif
