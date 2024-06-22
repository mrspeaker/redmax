#ifndef PLANE_H
#define PLANE_H

#include <raylib-cpp.hpp>

namespace rm {

class plane {
public:
    raylib::Matrix transform;
    raylib::Vector3 pos;
    raylib::Vector3 rot;
    raylib::Vector3 scale;

    float speed;

    plane();
    void update(float dt, bool is_left, bool is_right, bool is_up, bool is_down);
    bool flying();
};

} // namespace rm

#endif // PLANE_H
