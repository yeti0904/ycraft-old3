#include "blockdefs.hh"
#include "util.hh"

bool Blockdefs::Exists(blockID_t id) {
	return defs.count(id) != 0;
}

void Blockdefs::Create(
	blockID_t id, std::string name, uint32_t textureID, BlockType type,
	bool emitsLight, lightLevel_t brightness
) {
	defs[id] = {name, textureID, type, emitsLight, brightness};
	Util::Log("Created new block %s (%i)", name.c_str(), id);
}
