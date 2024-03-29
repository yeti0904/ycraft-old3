#ifndef YCRAFT_TYPES_HH
#define YCRAFT_TYPES_HH

#include "_components.hh"

struct Vec2 {
	int32_t x, y;
};

struct UVec2 { // unsigned Vec2
	uint32_t x, y;
};

struct FVec2 { // float Vec2
	float x, y;
};

struct WVec2 { // word Vec2
	size_t x, y;
};

typedef SDL_Rect Rect;

struct FRect { // float Rect
	float x, y, w, h;
};

#endif
