#pragma once
#include "_components.hh"
#include "types.hh"

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
		void Generate(UVec2 p_size);
};
