#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#import <item.hpp>

namespace rm {

struct slot {
    item_type type=item_type::NONE;
    bool stackable=false;
    int num=0;
};

struct inventory {
    int cur_slot=0;
    static const int MAX_SLOTS = 5;
    rm::slot slots[MAX_SLOTS];
    void add_item(item_type type, int amount);
};

}; // namespace

#endif // INVENTORY_HPP
