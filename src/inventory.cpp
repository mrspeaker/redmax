#include <inventory.hpp>

void rm::inventory::add_item(item_type type, int amount) {
    auto idx = -1;
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (slots[i].type == type) {
            idx = i;
            break;
        }
        if (idx == -1 && slots[i].type == item_type::NONE) {
            idx = i;
        }
    }
    if (idx == -1) {
        return;
    }
    slots[idx].type = type;
    slots[idx].num += amount;
}
