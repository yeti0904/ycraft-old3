#include "player.hh"
#include "constants.hh"
#include "collision.hh"

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

void Player::GoUp(double delta, double multiplier, Level& level, Blockdefs& defs) {
	oldPosition =  position;
	position.y  -= 40 * (delta * 0.0001) * multiplier;
	state       =  PlayerState::Moving;

	// collision
	std::vector <Vec2> blockPositions = GetTouchingBlocks();
	for (auto& block : blockPositions) {
		if (!level.ValidBlock(block)) {
			continue;
		}
		if (level.SolidBlock(block, defs)) {
			if (TouchingBlock(block)) {
				position.y = ceil(position.y);
			}
		}
	}
}

void Player::GoDown(double delta, double multiplier, Level& level, Blockdefs& defs) {
	oldPosition =  position;
	position.y  += 40 * (delta * 0.0001) * multiplier;
	state       =  PlayerState::Moving;
	
	// collision
	std::vector <Vec2> blockPositions = GetTouchingBlocks();
	for (auto& block : blockPositions) {
		if (!level.ValidBlock(block)) {
			continue;
		}
		if (level.SolidBlock(block, defs)) {
			if (TouchingBlock(block)) {
				position.y = floor(position.y);
			}
		}
	}
}

void Player::GoLeft(double delta, double multiplier, Level& level, Blockdefs& defs) {
	oldPosition =  position;
	position.x  -= 40 * (delta * 0.0001) * multiplier;
	state       =  PlayerState::Moving;

	// collision
	std::vector <Vec2> blockPositions = GetTouchingBlocks();
	for (auto& block : blockPositions) {
		if (!level.ValidBlock(block)) {
			continue;
		}
		if (level.SolidBlock(block, defs)) {
			if (TouchingBlock(block)) {
				position.x = ceil(position.x);
			}
		}
	}
}

void Player::GoRight(double delta, double multiplier, Level& level, Blockdefs& defs) {
	oldPosition =  position;
	position.x  += 40 * (delta * 0.0001) * multiplier;
	state       =  PlayerState::Moving;

	// collision
	std::vector <Vec2> blockPositions = GetTouchingBlocks();
	for (auto& block : blockPositions) {
		if (!level.ValidBlock(block)) {
			continue;
		}
		if (level.SolidBlock(block, defs)) {
			if (TouchingBlock(block)) {
				position.x = floor(position.x);
			}
		}
	}
}

void Player::EdgeCollision(Level& level) {
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

FVec2 Player::CorrectPosition() {
	return {
		round(position.x * 10) / 10,
		round(position.y * 10) / 10
	};
}

std::vector <Vec2> Player::GetTouchingBlocks() {
	FVec2 corrected = CorrectPosition();

	return {
		{(int) floor(corrected.x), (int) floor(corrected.y)},
		{(int) ceil(corrected.x), (int) floor(corrected.y)},
		{(int) floor(corrected.x), (int) ceil(corrected.y)},
		{(int) ceil(corrected.x), (int) ceil(corrected.y)}
	};
}

bool Player::TouchingBlock(Vec2 block) {
	FVec2 corrected = CorrectPosition();

	return Collision::RectVsRect(
		{corrected.x, corrected.y, GAME_BLOCK_SIZE, GAME_BLOCK_SIZE},
		{(float) block.x, (float) block.y, GAME_BLOCK_SIZE, GAME_BLOCK_SIZE}
	);
}
