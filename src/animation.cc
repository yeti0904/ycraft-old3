#include "animation.hh"

Animation::Animation() {
	frame = 0;
}

void Animation::NextFrame() {
	frame = (frame + 1) % frames.size();
}

textureID_t Animation::GetFrame() {
	return frames[frame];
}
