#include "player.hh"
#include "constants.hh"

Player::Player() {
	position    = {0.0, 0.0};
	oldPosition = position;
	textureID   = 240;
	noclipping  = false;
	updates     = 0;
	
	walkAnimation.frames = {241, 242};
}

void Player::Reset() {
	state = PlayerState::Static;
}

void Player::Update() {
	++ updates;
	switch (state) {
		case PlayerState::Static: return;
		case PlayerState::Moving: {
			if (updates % 10 == 0) {
				walkAnimation.NextFrame();
			}
			break;
		}
	}
	if (updates % 60 == 0) {
		updates = 0;
	}
}

void Player::GoUp(double delta, double multiplier) {
	oldPosition =  position;
	position.y  -= 40 * (delta * 0.0001) * multiplier;
	state       =  PlayerState::Moving;
}

void Player::GoDown(double delta, double multiplier) {
	oldPosition =  position;
	position.y  += 40 * (delta * 0.0001) * multiplier;
	state       =  PlayerState::Moving;
}

void Player::GoLeft(double delta, double multiplier) {
	oldPosition =  position;
	position.x  -= 40 * (delta * 0.0001) * multiplier;
	state       =  PlayerState::Moving;
}

void Player::GoRight(double delta, double multiplier) {
	oldPosition =  position;
	position.x  += 40 * (delta * 0.0001) * multiplier;
	state       =  PlayerState::Moving;
}

void Player::Collision(Level level) {
	if (
		(position.x < 0) ||
		(position.y < 0) ||
		(position.x > level.size.x - 1) ||
		(position.y > level.size.y - 1)
	) {
		position = oldPosition;
	}
}

textureID_t Player::GetTextureID() {
	switch (state) {
		case PlayerState::Static: return textureID;
		case PlayerState::Moving: return walkAnimation.GetFrame();
	}
	return 0;
}
