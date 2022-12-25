#ifndef YCRAFT_LEVEL_HH
#define YCRAFT_LEVEL_HH

#include "_components.hh"
#include "types.hh"
#include "blockdefs.hh"
#include "light.hh"

struct RawLayerData {
	std::vector <blockID_t> data;
};

struct RawLevelData {
	uint16_t                   version;
	uint32_t                   width;
	uint32_t                   height;
	float                      playerX;
	float                      playerY;
	uint16_t                   layerAmount;
	std::vector <RawLayerData> layerData;
};

struct LevelLayer {
	LevelLight                            light;
	std::vector <std::vector <blockID_t>> front;
	std::vector <std::vector <blockID_t>> back;
};

class Level {
	public:
		// variables
		std::vector <LevelLayer> layers;
		UVec2                    size;
		std::string              worldsPath;
		std::string              name;

		// functions
		Level() {}
		void         Generate();
		void         Destroy();
		bool         ValidBlock(Vec2 block);
		bool         SolidBlock(Vec2 block, Blockdefs& blockdefs);
		RawLevelData GetRawData();
		void         LoadFromRawLayerData(
			RawLayerData& layerData, UVec2 layerSize, size_t layer
		);
		void         LoadLevel(std::string path);
		void         SaveLevel(std::string path);
		void         Save();
};

#endif
