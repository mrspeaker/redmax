#include <tile.hpp>
#include <iostream>

rm::tile::tile()
    : type(0),
      next_type(-1) {}

bool rm::tile::update() {
    ticks++;
    if (next_type != 255) {
        type = next_type;
        next_type = -1;
        ticks = 0;
        return true;
    }
    if (type == 2 && ticks > 1000) {
        type = 3;
        ticks = 0;
        return true;
    }
    return false;
};
