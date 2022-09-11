#include "text.hh"
#include "colours.hh"
#include "util.hh"

TextComponents::TextComponents() {
	font = nullptr;
}

void TextComponents::Init(std::string fontPath) {
	if (TTF_Init() == -1) {
		Util::Error("Failed to initialise SDL_ttf: %s", TTF_GetError());
	}

	font = TTF_OpenFont(fontPath.c_str(), 16);
	if (font == nullptr) {
		Util::Error("Failed to open font: %s", TTF_GetError());
	}
}

void TextComponents::Free() {
	TTF_CloseFont(font);
	TTF_Quit();
}

void TextComponents::RenderText(
	SDL_Renderer* renderer, std::string text, Vec2 pos, float size, bool shadow
) {
	if (text.empty()) {
		return;
	}

	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
	SDL_Colour   colour = {
		(Uint8) (shadow? 0 : 255),
		(Uint8) (shadow? 0 : 255),
		(Uint8) (shadow? 0 : 255),
		255
	};
	SDL_Rect     textRect;
	int8_t       shadowOffset = (int) round(size);

	textSurface = TTF_RenderText_Solid(font, text.c_str(), colour);
	if (textSurface == nullptr) {
		Util::Error("TTF_RenderText_Solid error: %s", TTF_GetError());
	}
	textRect = {
		pos.x, pos.y, 
		(int)((float) textSurface->w * size), (int)((float)textSurface->h * size)
	};
	if (shadow) {
		textRect.x += shadowOffset;
		textRect.y += shadowOffset;
	}
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	if (textTexture == nullptr) {
		Util::Error("SDL_CreateTextureFromSurface returned NULL: %s\n", SDL_GetError());
	}

	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	if (shadow) {
		colour      = Colours::white;
		textRect.x -= shadowOffset;
		textRect.y -= shadowOffset;

		textSurface = TTF_RenderText_Solid(font, text.c_str(), colour);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

		if (textTexture == nullptr) {
			Util::Error(
			"SDL_CreateTextureFromSurface returned NULL: %s\n",
				SDL_GetError()
			);
		}

		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}
}

Vec2 TextComponents::GetTextSize(std::string text, float size) {
	if (text.empty()) {
		return {0, 0};
	}

	SDL_Surface* textSurface;
	SDL_Colour   colour = Colours::white;
	SDL_Rect     textRect;

	textSurface = TTF_RenderText_Solid(font, text.c_str(), colour);
	if (textSurface == nullptr) {
		Util::Error("TTF_RenderText_Solid returned NULL: %s", TTF_GetError());
	}
	textRect = {
		0, 0,
		(int)((float) textSurface->w * size), (int)((float)textSurface->h * size)
	};

	SDL_FreeSurface(textSurface);

	return {textRect.w, textRect.h};	
}
