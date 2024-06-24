#ifndef TRANS_HPP
#define TRANS_HPP

#include <raylib-cpp.hpp>

namespace rm {

class trans {
public:
    raylib::Matrix transform{};
    raylib::Vector3 pos{0, 0, 0};
    raylib::Vector3 rot{0, 0, 0};
    raylib::Vector3 scale{1, 1, 1};

    trans()=default;
};

} // namespace rm

#endif // TRANS
