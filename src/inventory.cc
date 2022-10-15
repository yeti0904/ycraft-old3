#include "inventory.hh"

Inventory::Inventory() {
	for (auto& item : Hotbar()) {
		item = {true, 0, 0};
	}
	hotbarSelection = 0;
}

InventoryLine& Inventory::Hotbar() {
	return inventory.back();
}