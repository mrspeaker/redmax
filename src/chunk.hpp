#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <raylib-cpp.hpp>

#import <vector>
// #import <memory>
#import <tile.hpp>
#import <observer.hpp>

namespace rm {

constexpr int width = 16;
constexpr int height = 16;

class chunk : public subject{
 public:
    int col=0;
    float x=0.0;
    float z=0.0;
    float world_x=0.0;
    float world_z=0.0;
    std::vector<raylib::Vector3> trees;
    rm::tile *tiles;
    bool dirty=false;
    chunk();
    ~chunk() {
        // Someone is deleting this...
        // raylib? where?
        //delete[] tiles;
    }
    void update(std::vector<chunk>& chunks);
};

} // namespace rm


#endif // CHUNK_HPP
