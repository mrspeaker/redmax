#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <raylib-cpp.hpp>

namespace rm {

class camera {
public:
    raylib::Camera3D cam;
    camera();
};

} // namespace rm

#endif // CAMERA_HPP
