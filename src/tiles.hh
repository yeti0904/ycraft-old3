#ifndef YCRAFT_TILES_HH
#define YCRAFT_TILES_HH

#include "_components.hh"
#include "types.hh"

class TileSheet {
	public:
		// variables
		uint32_t     tileSize;
		SDL_Texture* image;

		// functions
		TileSheet() {}
		void  Init(SDL_Renderer* renderer, std::string path, uint32_t p_tileSize);
		void  Free();
		UVec2 GetTexturePosition(uint32_t id);
		void  RenderTile(SDL_Renderer* renderer, uint32_t id, Vec2 pos);
};

#endif
