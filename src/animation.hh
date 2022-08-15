#pragma once
#include "_components.hh"

class Animation {
	public:
		std::vector <textureID_t> frames;
		size_t                    frame;

		Animation();
		void        NextFrame();
		textureID_t GetFrame();
};
