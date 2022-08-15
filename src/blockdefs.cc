#include "blockdefs.hh"
#include "util.hh"

bool Blockdefs::Exists(blockID_t id) {
	return defs.count(id) != 0;
}

void Blockdefs::Create(
	blockID_t id, std::string name, uint32_t textureID, BlockType type
) {
	defs[id] = {name, textureID, type};
	Util::Log("Created new block %s (%i)", name.c_str(), id);
}
