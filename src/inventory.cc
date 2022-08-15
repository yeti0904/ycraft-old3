#include "inventory.hh"

Inventory::Inventory() {
	for (auto& item : hotbar) {
		item = {true, 0, 0};
	}
	hotbarSelection = 0;
}
