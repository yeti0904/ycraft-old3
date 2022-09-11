#ifndef YCRAFT_LEVEL_HH
#define YCRAFT_LEVEL_HH

#include "_components.hh"
#include "types.hh"
#include "blockdefs.hh"

struct LevelData {
	uint16_t version;
	uint32_t width;
	uint32_t height;
	uint16_t layerAmount;
	void*    layerData;
};

struct LevelLayer {
	std::vector <std::vector <blockID_t>> front;
	std::vector <std::vector <blockID_t>> back;
};

class Level {
	public:
		// variables
		std::vector <LevelLayer> layers;
		UVec2                    size;

		// functions
		Level() {}
		void Generate();
		void Destroy();
		bool ValidBlock(Vec2 block);
		bool SolidBlock(Vec2 block, Blockdefs& blockdefs);
};

#endif
