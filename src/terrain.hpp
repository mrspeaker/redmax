#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#import <vector>
#import <chunk.hpp>
#import <tile.hpp>

namespace rm {

class terrain {
 public:
    int width_in_chunks;
    int height_in_chunks;
    float width;
    float height;
    std::vector<chunk> chunks;
    terrain();
    rm::tile *get_tile_from_pos(float x, float y);
};

} // namespace rm


#endif // TERRAIN_HPP
