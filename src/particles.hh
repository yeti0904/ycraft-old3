#ifndef YCRAFT_PARTICLES_HH
#define YCRAFT_PARTICLES_HH

#include "_components.hh"
#include "video.hh"
#include "types.hh"
#include "tiles.hh"

namespace Particles {
	struct Particle {
		FVec2  position;
		Vec2   textureSource;
		FVec2  velocity;
	};

	class Manager {
		public:
			// variables
			std::vector <Particle> particles;
			TileSheet*             tileSheet;

			// functions
			Manager();
			void UpdateParticles();
			void NewParticle(textureID_t texureID, UVec2 blockPos);
			void Render(VideoComponents& video, FVec2 camera);
	};
}

#endif