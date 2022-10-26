#ifndef YCRAFT_INVENTORY_HH
#define YCRAFT_INVENTORY_HH

#include "_components.hh"

struct InventoryEntry {
	bool      empty;
	blockID_t block;
	uint16_t  amount;
};

typedef std::array <std::array <InventoryEntry, 9>, 5> InventoryArray;
typedef std::array <InventoryEntry, 9>                 InventoryLine;

class Inventory {
	public:
		// variables
		InventoryArray inventory;
		size_t         hotbarSelection;

		// functions
		Inventory();
		InventoryLine& Hotbar();
		void           MakeEmpty();
};

#endif
