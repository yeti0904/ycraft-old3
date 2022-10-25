#include "inventory.hh"

Inventory::Inventory() {
	for (auto& line : inventory) {
		for (auto& item : line) {
			item = {true, 0, 0};
		}
	}
	hotbarSelection = 0;
}

InventoryLine& Inventory::Hotbar() {
	return inventory.back();
}