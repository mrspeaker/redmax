#ifndef TILE_HPP
#define TILE_HPP

namespace rm {

class tile {
public:
    unsigned char type;
    unsigned char next_type;
    int ticks;
    bool update();
    tile();
};

}

#endif // TILE_HPP
