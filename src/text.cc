#include "text.hh"

TextComponents::TextComponents() {
	font = nullptr;
}

void TextComponents::Init(std::string fontPath) {
	if (TTF_Init() == -1) {
		fprintf(stderr, "[ERROR] Failed to initialise SDL_ttf: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	font = TTF_OpenFont(fontPath.c_str(), 16);
	if (font == nullptr) {
		fprintf(stderr, "[ERROR] Failed to open font: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
}

void TextComponents::Free() {
	TTF_CloseFont(font);
	TTF_Quit();
}

void TextComponents::RenderText(
	SDL_Renderer* renderer, std::string text, Vec2 pos, float size, bool shadow
) {
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
		fprintf(
			stderr,
			"[ERROR] SDL_CreateTextureFromSurface returned NULL: %s\n",
			SDL_GetError()
		);
		exit(EXIT_FAILURE);
	}

	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	if (shadow) {
		colour      = {255, 255, 255, 255};
		textRect.x -= shadowOffset;
		textRect.y -= shadowOffset;

		textSurface = TTF_RenderText_Solid(font, text.c_str(), colour);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

		if (textTexture == nullptr) {
			fprintf(
				stderr,
				"[ERROR] SDL_CreateTextureFromSurface returned NULL: %s\n",
				SDL_GetError()
			);
			exit(EXIT_FAILURE);
		}

		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}
}

Vec2 TextComponents::GetTextSize(std::string text, float size) {
	SDL_Surface* textSurface;
	SDL_Colour   colour = {255, 255, 255, 255};
	SDL_Rect     textRect;

	textSurface = TTF_RenderText_Solid(font, text.c_str(), colour);
	textRect = {
		0, 0,
		(int)((float) textSurface->w * size), (int)((float)textSurface->h * size)
	};

	SDL_FreeSurface(textSurface);

	return {textRect.w, textRect.h};	
}
