#ifndef INVENTORY_HPP
#define INVENTORY_HPP

namespace rm {

enum class slot_type {
    NONE,
    SEEDS,
};

struct slot {
    slot_type type=slot_type::NONE;
    bool stackable=false;
    int num=0;
};

struct inventory {
    rm::slot slots[5];
    void add_item(slot_type type, int amount);
};

}; // namespace

#endif // INVENTORY_HPP
