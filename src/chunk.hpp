#ifndef CHUNK_HPP
#define CHUNK_HPP

#import <vector>
#import <Vector3.hpp>
#import <memory>

namespace rm {

constexpr int width = 16;
constexpr int height = 16;

class chunk {
 public:
    int col;
    float x;
    float z;
    std::vector<raylib::Vector3> trees;
    unsigned char *tiles;
    chunk();
    ~chunk() {
        // Someone is deleting this...
        //delete[] tiles;
    }
};

} // namespace rm


#endif // CHUNK_HPP
