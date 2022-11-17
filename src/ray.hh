#ifndef YCRAFT_RAY_HH
#define YCRAFT_RAY_HH

#include "_components.hh"
#include "types.hh"

namespace Ray {
	struct Ray {
		FVec2    pos;
		uint16_t dir;
	};
	float DegreesToRadians(float degrees);
	Ray MoveInDirection(Ray ray, float distance);
}

#endif