#pragma once
#include "_components.hh"
#include "types.hh"
#include "level.hh"
#include "inventory.hh"
#include "animation.hh"
#include "blockdefs.hh"

enum class PlayerState {
	Static = 0,
	Moving
};

class Player {
	public:
		// variables
		FVec2       oldPosition;
		FVec2       position;
		textureID_t textureID;
		bool        noclipping;
		Inventory   inventory;
		PlayerState state;
		size_t      updates;

		// animations
		Animation walkAnimation;

		// functions
		Player();
		void        Reset();
		void        Update();
		void        GoUp(double delta, double multiplier, Level& level, Blockdefs& defs);
		void        GoDown(double delta, double multiplier, Level& level, Blockdefs& defs);
		void        GoLeft(double delta, double multiplier, Level& level, Blockdefs& defs);
		void        GoRight(double delta, double multiplier, Level& level, Blockdefs& defs);
		void        EdgeCollision(Level& level);
		textureID_t GetTextureID();
};
