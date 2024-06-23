#include <inventory.hpp>

void rm::inventory::add_item(slot_type slot_type, int amount) {
    slots[0].type = slot_type;
    slots[0].num += amount;
}
