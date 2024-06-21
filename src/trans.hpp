#ifndef TRANS_HPP
#define TRANS_HPP

#include <raylib-cpp.hpp>

namespace rm {

class trans {
public:
    raylib::Matrix transform;
    raylib::Vector3 pos;
    raylib::Vector3 rot;
    raylib::Vector3 scale;
};

} // namespace rm

#endif // TRANS
