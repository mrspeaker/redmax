#include <tile.hpp>

void rm::tile::update() {
    ticks+=type + 1;
  if (ticks > 100) {
      ticks = 0;
      type++;
      if (type > 1) {
          type = 0;
      }
  }
};
