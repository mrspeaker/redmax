#include <tile.hpp>

bool rm::tile::update() {
    if (ticks == 1000) {
        type = 2;
        ticks = 0;
        return true;
    }
    return false;
};
