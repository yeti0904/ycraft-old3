#include "level.hh"
#include "util.hh"
#include "constants.hh"
#include "bits.hh"

void Level::Generate() {
	layers.push_back({});
	layers[0].front.resize(size.y);
	layers[0].back.resize(size.y);
	
	for (size_t i = 0; i < size.y; ++i) {
		layers[0].front[i].resize(size.x);
		layers[0].back[i].resize(size.x);
		for (size_t j = 0; j < size.x; ++j) {
			layers[0].front[i][j] = 0;
			layers[0].back[i][j]  = 3;
		}
	}
}

void Level::Destroy() {
	layers = {};
}

bool Level::ValidBlock(Vec2 block) {
	return (
		(block.x >= 0) && (block.y >= 0) &&
		(block.x < (int) size.x) && (block.y < (int) size.y)
	);
}

bool Level::SolidBlock(Vec2 block, Blockdefs& blockdefs) {
	return (blockdefs.defs[layers[0].front[block.y][block.x]].type == BlockType::Solid);
}

RawLevelData Level::GetRawData() {
	RawLevelData ret;
	ret.version     = GAME_LEVELDATA_VERSION;
	ret.width       = size.x;
	ret.height      = size.y;
	ret.playerX     = size.x / 2;
	ret.playerY     = size.y / 2;
	ret.layerAmount = layers.size();

	// generate raw layer data
	for (auto& layer : layers) {
		RawLayerData toPush;

		for (auto& line : layer.front) {
			for (auto& block : line) {
				toPush.data.push_back(block);
			}
		}
		for (auto& line : layer.back) {
			for (auto& block : line) {
				toPush.data.push_back(block);
			}
		}

		ret.layerData.push_back(toPush);
	}

	return ret;
}

void Level::LoadFromRawLayerData(
	RawLayerData& layerData, UVec2 layerSize, size_t layer
) {
	size = layerSize;
	if (layer >= layers.size()) {
		layers.resize(layer - 1);
	}
	layers[layer].front.resize(layerSize.y);
	for (auto& line : layers[layer].front) {
		line.resize(layerSize.x);
	}
	layers[layer].back.resize(layerSize.y);
	for (auto& line : layers[layer].back) {
		line.resize(layerSize.x);
	}

/*
	for (size_t i = 0; i < layerSize.x * layerSize.y; ++i) {
		const size_t x = i == 0? 0 : layerSize.x % i;
		const size_t y = i == 0? 0 : i / layerSize.x;
		layers[layer].front[y][x] = layerData.data[i];
	}
	const UVec2 totalSize = {layerSize.x * 2, layerSize.y * 2};
	for (size_t i = layerSize.x * layerSize.y; i < 2 * totalSize.x * totalSize.y; ++i) {
		const size_t x = totalSize.x % i;
		const size_t y = i / totalSize.x;
		layers[layer].back[y][x] = layerData.data[i];
	}
*/
/*
	for (size_t i = 0; i < layerSize.x * layerSize.y; ++i) {
		for (size_t y = 0, i = 0; y < layerSize.y; ++y) {
			for (size_t x = 0; x < layerSize.x; ++x, ++i) {
				layers[layer].front[y][x] = layerData.data[i];
			}
		}
	}
	for (size_t i = layerSize.x * layerSize.y; i < 2 * layerSize.x * layerSize.y; ++i) {
		for (size_t y = 0, i = 0; y < layerSize.y; ++y) {
			for (size_t x = 0; x < layerSize.x; ++x, ++i) {
				layers[layer].front[y][x] = layerData.data[i];
			}
		}
	}
*/

	size_t srcIndex = 0;

	for (size_t y = 0; y < layerSize.y; ++y) {
		for (size_t x = 0; x < layerSize.x; ++x, ++ srcIndex) {
			layers[layer].front[y][x] = layerData.data[srcIndex];
		}
	}

	for (size_t y = 0; y < layerSize.y; ++y) {
		for (size_t x = 0; x < layerSize.x; ++x, ++ srcIndex) {
			layers[layer].back[y][x] = layerData.data[srcIndex];
	    }
	}
}

void Level::LoadLevel(std::string path) {
	std::ifstream fhnd(path, std::ios::out | std::ios::binary);
	if (!fhnd.good()) {
		Util::Error("Failed to open %s", path.c_str());
	}
	RawLevelData data;

	// read version
	{
		std::vector <uint8_t> bytes(2, 0);
		fhnd.read((char*) bytes.data(), bytes.size());
		data.version = Bits::Join16(bytes);
	}

	// read width
	{
		std::vector <uint8_t> bytes(4, 0);
		fhnd.read((char*) bytes.data(), bytes.size());
		data.width = Bits::Join32(bytes);
	}

	// read height
	{
		std::vector <uint8_t> bytes(4, 0);
		fhnd.read((char*) bytes.data(), bytes.size());
		data.height = Bits::Join32(bytes);
	}

	// read player X
	{
		std::vector <uint8_t> bytes(4, 0);
		fhnd.read((char*) bytes.data(), bytes.size());
		data.playerX = (float) Bits::Join32(bytes) / 100;
	}

	// read player Y
	{
		std::vector <uint8_t> bytes(4, 0);
		fhnd.read((char*) bytes.data(), bytes.size());
		data.playerY = (float) Bits::Join32(bytes) / 100;
	}

	// read layer amount
	{
		std::vector <uint8_t> bytes(2, 0);
		fhnd.read((char*) bytes.data(), bytes.size());
		data.layerAmount = Bits::Join16(bytes);
	}

	// read layer data
	{
		layers = {};
		layers.resize(data.layerAmount);
		size   = {data.width, data.height};

		for (auto& layer : layers) {
			layer.front.resize(size.y);
			for (auto& line : layer.front) {
				line.resize(size.x);
			}
			layer.back.resize(size.y);
			for (auto& line : layer.back) {
				line.resize(size.x);
			}
		}

		for (int i = 0; i < data.layerAmount; ++i) {
			RawLayerData layer;
			for (int j = 0; j < 2; ++j) {
				for (size_t k = 0; k < size.x * size.y; ++k) {
					std::vector <uint8_t> bytes(sizeof(blockID_t), 0);
					fhnd.read((char*) bytes.data(), bytes.size());
					layer.data.push_back(Bits::Join16(bytes));
				}
			}
			data.layerData.push_back(layer);
		}
	}

	// load level
	for (size_t i = 0; i < data.layerData.size(); ++i) {
		LoadFromRawLayerData(data.layerData[i], size, i);
	}
}

void Level::SaveLevel(std::string path) {
	std::ofstream fhnd(path, std::ios::out | std::ios::binary);
	if (!fhnd.good()) {
		Util::Error("Failed to open %s", path.c_str());
	}

	RawLevelData rawData = GetRawData();

	// write version
	{
		auto data = Bits::Split16(rawData.version);
		fhnd.write((char*) data.data(), data.size());
	}

	// write width
	{
		auto data = Bits::Split32(rawData.width);
		fhnd.write((char*) data.data(), data.size());
	}

	// write height
	{
		auto data = Bits::Split32(rawData.height);
		fhnd.write((char*) data.data(), data.size());
	}

	// write player X
	{
		auto data = Bits::Split32(rawData.playerX);
		fhnd.write((char*) data.data(), data.size());
	}

	// write player Y
	{
		auto data = Bits::Split32(rawData.playerY);
		fhnd.write((char*) data.data(), data.size());
	}

	// write layerAmount
	{
		auto data = Bits::Split16(rawData.layerAmount);
		fhnd.write((char*) data.data(), data.size());
	}

	// write layerData
	for (auto& layer : rawData.layerData) {
		// fhnd.write((char*) layer.data.data(), layer.data.size());
		for (auto& block : layer.data) {
			auto data = Bits::Split16(block);
			fhnd.write((char*) data.data(), data.size());
		}
	}

	fhnd.close();
}

void Level::Save() {
	SaveLevel(worldsPath + "/" + name);
}