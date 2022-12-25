#ifndef YCRAFT_BLOCKDEFS_HH
#define YCRAFT_BLOCKDEFS_HH

#include "_components.hh"
#include "light.hh"

enum class BlockType {
	Gas = 0,
	Liquid,
	Solid
};

struct Block {
	std::string name;
	uint32_t    textureID;
	BlockType   type;

	bool         emitsLight;
	lightLevel_t brightness;
};

class Blockdefs {
	public:
		// variables
		std::unordered_map <blockID_t, Block> defs;

		// functions
		Blockdefs() {}
		bool Exists(blockID_t id);
		void Create(
			blockID_t id, std::string name, uint32_t textureID, BlockType type,
			bool emitsLight, lightLevel_t brightness
		);
};

#endif
