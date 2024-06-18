#include <raylib-cpp.hpp>
#include <camera.hpp>

rm::camera::camera() :
    cam(
        (raylib::Vector3){ 0.001f, 200.0f, 0.0f },
        (raylib::Vector3){ 0.0f, 0.0f, 0.0f },
        (raylib::Vector3){ 0.0f, 1.0f, 0.0f },
        40.0f,
        CAMERA_PERSPECTIVE) {}
