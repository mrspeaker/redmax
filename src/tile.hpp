#ifndef TILE_HPP
#define TILE_HPP

namespace rm {

class tile {
public:
  unsigned char type;
  int ticks;
  void update();
};

}

#endif // TILE_HPP
