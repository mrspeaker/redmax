#ifndef CHUNK_HPP
#define CHUNK_HPP

#import <vector>
#import <Vector3.hpp>

namespace rm {

class chunk {
 public:
    float x;
    float z;
    int col;
    std::vector<int> tiles;
    std::vector<raylib::Vector3> trees;
    chunk();
};

} // namespace rm


#endif // CHUNK_HPP
