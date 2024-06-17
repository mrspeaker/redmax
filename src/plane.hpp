#ifndef PLANE_H
#define PLANE_H

#include <Matrix.hpp>
#include <Vector3.hpp>

namespace rm {

class plane {
public:
    raylib::Matrix transform;
    raylib::Vector3 pos;
    raylib::Vector3 rot;
    raylib::Vector3 scale;

    float speed;

    plane();
    void update(float dt, bool is_left, bool is_right, bool is_up, bool is_down, bool is_action);
};

} // namespace rm

#endif // PLANE_H
