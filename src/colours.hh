#ifndef YCRAFT_COLOURS_HH
#define YCRAFT_COLOURS_HH

#include "_components.hh"

namespace Colours {
	constexpr SDL_Color white   = {255, 255, 255, 255};
	constexpr SDL_Color black   = {0, 0, 0, 255};
	constexpr SDL_Color grey    = {54, 54, 54, 255};
	constexpr SDL_Color nothing = {0, 0, 0, 0};
	constexpr SDL_Color transparentBlack = {0, 0, 0, 127};
}

#endif
