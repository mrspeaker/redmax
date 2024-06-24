#ifndef CHUNK_HPP
#define CHUNK_HPP

#import <vector>
#import <Vector3.hpp>
#import <memory>
#import <tile.hpp>
#import <observer.hpp>

namespace rm {

constexpr int width = 16;
constexpr int height = 16;

class chunk : public subject{
 public:
    int col;
    float x;
    float z;
    float world_x;
    float world_z;
    std::vector<raylib::Vector3> trees;
    rm::tile *tiles;
    bool dirty;
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
