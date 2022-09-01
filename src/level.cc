#include "level.hh"

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
