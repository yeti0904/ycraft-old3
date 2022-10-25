#ifndef YCRAFT_COLOURS_HH
#define YCRAFT_COLOURS_HH

#include "_components.hh"

namespace Colours {
	constexpr SDL_Color white            = {255, 255, 255, 255};
	constexpr SDL_Color black            = {31, 16, 42, 255};
	constexpr SDL_Color grey             = {166, 133, 159, 255};
	constexpr SDL_Color nothing          = {0, 0, 0, 0};
	constexpr SDL_Color transparentBlack = {31, 16, 42, 127};
	constexpr SDL_Color lightgrey        = {217, 189, 200, 255};

	constexpr SDL_Color bg = {74, 48, 82, 255};
}

#endif
