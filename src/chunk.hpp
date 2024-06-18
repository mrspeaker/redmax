#ifndef CHUNK_HPP
#define CHUNK_HPP

#import <vector>
#import <Vector3.hpp>

namespace rm {

class chunk {
 public:
    int col;
    float x;
    float z;
    //std::vector<int> tiles;
    std::vector<raylib::Vector3> trees;
    chunk();
};

} // namespace rm


#endif // CHUNK_HPP
