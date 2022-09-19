#include "tiles.hh"
#include "util.hh"

void TileSheet::Init(SDL_Renderer* renderer, std::string path, uint32_t p_tileSize) {
	image    = IMG_LoadTexture(renderer, path.c_str());
	tileSize = p_tileSize;
	SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);

	if (image == nullptr) {
		Util::Error("IMG_LoadTexture returned NULL: %s", IMG_GetError());
		exit(EXIT_FAILURE);
	}
}

void TileSheet::Free() {
	SDL_DestroyTexture(image);
}

UVec2 TileSheet::GetTexturePosition(uint32_t id) {
	SDL_Point textureSize;
	SDL_QueryTexture(image, nullptr, nullptr, &textureSize.x, &textureSize.y);

	return {
		id % (textureSize.x / tileSize) * tileSize,
		id / (textureSize.x / tileSize) * tileSize
	};
}

void TileSheet::RenderTile(SDL_Renderer* renderer, uint32_t id, Vec2 pos) {
	UVec2    texturePos = GetTexturePosition(id);
	SDL_Rect destRect = {
		pos.x, pos.y, (int) tileSize, (int) tileSize
	};
	SDL_Rect sourceRect = {
		(int) texturePos.x, (int) texturePos.y, (int) tileSize, (int) tileSize
	};

	SDL_RenderCopy(renderer, image, &sourceRect, &destRect);
}
