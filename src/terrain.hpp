#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#import <vector>
#import <chunk.hpp>

namespace rm {

class terrain {
 public:
    std::vector<chunk> chunks;
    terrain();
};

} // namespace rm


#endif // TERRAIN_HPP
