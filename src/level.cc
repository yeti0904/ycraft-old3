#include "level.hh"

void Level::Generate(UVec2 p_size) {
	layers.push_back({});
	size = p_size;
	layers[0].front.resize(p_size.y);
	layers[0].back.resize(p_size.y);
	
	for (size_t i = 0; i < p_size.y; ++i) {
		layers[0].front[i].resize(p_size.x);
		layers[0].back[i].resize(p_size.x);
		for (size_t j = 0; j < p_size.x; ++j) {
			layers[0].front[i][j] = 0;
			layers[0].back[i][j]  = 3;
		}
	}
}
