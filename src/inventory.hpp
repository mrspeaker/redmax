#ifndef INVENTORY_HPP
#define INVENTORY_HPP

namespace rm {

enum class slot_type {
    NONE,
    SEEDS,
};

struct slot {
    slot_type type;
    bool stackable;
    int num;
};

struct inventory {
    rm::slot slots[5];
    void add_item(slot_type type, int amount);
    inventory()=default;
};

}; // namespace

#endif // INVENTORY_HPP
