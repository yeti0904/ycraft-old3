#include "particles.hh"
#include "constants.hh"
#include "util.hh"

Particles::Manager::Manager():
	tileSheet(nullptr)
{
	
}

void Particles::Manager::UpdateParticles() {
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		it->position.x -= it->velocity.x;
		it->position.y -= it->velocity.y;

		if (it->velocity.x > 0.0f) {
			it->velocity.x -= 0.01f;
			if (it->velocity.x < 0.01f) {
				it->velocity.x = 0.0f;
			}
		}
		if (it->velocity.x < 0.0f) {
			it->velocity.x += 0.01f;
			if (it->velocity.x > -0.01f) {
				it->velocity.x = 0.0f;
			}
		}
		if (it->velocity.y > 0.0f) {
			it->velocity.y -= 0.01f;
			if (it->velocity.y < 0.01f) {
				it->velocity.y = 0.0f;
			}
		}
		if (it->velocity.y < 0.0f) {
			it->velocity.y += 0.01f;
			if (it->velocity.y > -0.01f) {
				it->velocity.y = 0.0f;
			}
		}

		if ((it->velocity.x == 0.0f) && (it->velocity.y == 0.0f)) {
			particles.erase(it);
			-- it;
		}
	}
}

void Particles::Manager::NewParticle(textureID_t textureID, UVec2 blockPos) {
	Particle particle;
	particle.position = {
		(float) blockPos.x + Util::FRandomRange(0.0, 1.0),
		(float) blockPos.y + Util::FRandomRange(0.0, 1.0)
	};
	auto texturePos = tileSheet->GetTexturePosition(textureID);
	particle.textureSource = {
		(int) (texturePos.x + Util::RandomRange(0, GAME_BLOCK_SIZE - 2)),
		(int) (texturePos.y + Util::RandomRange(0, GAME_BLOCK_SIZE - 2))
	};
	particle.velocity = {
		Util::FRandomRange(-0.15, 0.15), Util::FRandomRange(-0.15, 0.15)
	};
	particles.push_back(particle);

	while (particles.size() > GAME_MAX_PARTICLES) {
		particles.erase(particles.begin());
	}
}

void Particles::Manager::Render(VideoComponents& video, FVec2 camera) {
	for (auto& particle : particles) {
		Vec2 particlePos = {
			(int) (particle.position.x * GAME_BLOCK_SIZE - camera.x * GAME_BLOCK_SIZE),
			(int) (particle.position.y * GAME_BLOCK_SIZE - camera.y * GAME_BLOCK_SIZE)
		};

		if (
			(particlePos.x < 0) ||
			(particlePos.y < 0) ||
			(particlePos.x > APP_SCREEN_SIZE_W) ||
			(particlePos.y > APP_SCREEN_SIZE_H)
		) {
			continue;
		}

		SDL_Rect destRect = {
			particlePos.x, particlePos.y, GAME_PARTICLE_SIZE, GAME_PARTICLE_SIZE
		};
		SDL_Rect sourceRect = {
			particle.textureSource.x, particle.textureSource.y,
			GAME_PARTICLE_SIZE, GAME_PARTICLE_SIZE
		};
		SDL_RenderCopy(video.renderer, tileSheet->image, &sourceRect, &destRect);
	}
}