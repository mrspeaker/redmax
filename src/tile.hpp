#ifndef TILE_HPP
#define TILE_HPP

namespace rm {

class tile {
public:
  unsigned char type;
  int ticks;
  bool update();
};

}

#endif // TILE_HPP
