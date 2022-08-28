#ifndef YCRAFT_ANIMATION_HH
#define YCRAFT_ANIMATION_HH

#include "_components.hh"

class Animation {
	public:
		std::vector <textureID_t> frames;
		size_t                    frame;

		Animation();
		void        NextFrame();
		textureID_t GetFrame();
};

#endif
