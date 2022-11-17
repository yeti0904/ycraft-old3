#include "mouse.hh"

Vec2& Mouse::Position() {
	static Vec2 pos = {-1, -1};

	return pos;
}

bool& Mouse::Pressed() {
	static bool pressed = false;

	return pressed;
}
