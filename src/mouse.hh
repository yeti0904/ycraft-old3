#ifndef YCRAFT_MOUSE_HH
#define YCRAFT_MOUSE_HH

#include "types.hh"

namespace Mouse {
	Vec2& Position();
	bool& Pressed();
	bool& Clicked(); // only lasts for 1 frame
}

#endif
