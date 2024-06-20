#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#import <vector>
#import <chunk.hpp>
#import <tile.hpp>

namespace rm {

class terrain {
 public:
    std::vector<chunk> chunks;
    terrain();
    rm::tile *get_tile_from_pos(float x, float y);
};

} // namespace rm


#endif // TERRAIN_HPP
