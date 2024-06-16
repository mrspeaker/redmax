#ifndef PLANE_H
#define PLANE_H

#include <Matrix.hpp>
#include <Vector3.hpp>

namespace rm {

class plane {
public:
    raylib::Vector3 pos;
    raylib::Vector3 rot;
    raylib::Vector3 scale;

    float speed;

    plane();
};

} // namespace rm

#endif // PLANE_H
