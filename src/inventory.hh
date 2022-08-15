#pragma once
#include "_components.hh"

struct InventoryEntry {
	bool      empty;
	blockID_t block;
	uint16_t  amount;
};

class Inventory {
	public:
		// variables
		std::array <InventoryEntry, 9> hotbar;
		size_t                         hotbarSelection;

		// functions
		Inventory();	
};
