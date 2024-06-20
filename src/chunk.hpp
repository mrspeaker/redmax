#ifndef CHUNK_HPP
#define CHUNK_HPP

#import <vector>
#import <Vector3.hpp>
#import <memory>
#import <tile.hpp>

namespace rm {

constexpr int width = 16;
constexpr int height = 16;

class chunk {
 public:
    int col;
    float x;
    float z;
    std::vector<raylib::Vector3> trees;
    rm::tile *tiles;
    bool dirty;
    chunk();
    ~chunk() {
        // Someone is deleting this...
        //delete[] tiles;
    }
    void update();
};

} // namespace rm


#endif // CHUNK_HPP
