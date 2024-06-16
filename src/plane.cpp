#include <plane.hpp>

#include <raylib-cpp.hpp>

rm::plane::plane() {
    speed = 0.0;
}

void rm::plane::update(float dt, bool is_left, bool is_right, bool is_up, bool is_down) {

    auto yaw = rot.y;
    auto roll = rot.z;

    const auto rot_speed = 1.0f * dt;
    auto yawo = 0.0;
    if (is_left) yawo += rot_speed;
    else if (is_right) yawo -= rot_speed;

    yaw += yawo;

    const auto roll_speed = 0.5f;
    if (yawo > 0) {
        if (roll > -1.0) {
            roll -= (roll_speed * roll > 0 ? 2 : 1) * dt;
        }
    }
    else if (yawo < 0) {
        if (roll < 1.0) {
            roll += (roll_speed * roll < 0 ? 2 : 1) * dt;
        }
    }
    else {
        if (roll > 0.0f) roll -= 0.5f * dt;
        else if (roll < 0.0f) roll += 0.5f * dt;
    }

    rot.y = yaw;
    rot.z = roll;

    if (is_down) {
        if (speed < 20.0) {
            speed += 10.0 * dt;
        }
        if (speed > 15.0) {
            pos.y += 5.0 * dt;
        }
    }
    if (is_up) {
        if (pos.y < 10.0 && speed > 0.0) {
            speed -= 10.0 * dt;
            if (speed < 0.0) speed = 0;
        }
        if (speed > 0) {
            if (pos.y > 10.0 || speed < 15.0) {
                pos.y -= 5.0 * dt;
            }
        }
    }

    transform = raylib::Matrix().RotateXYZ(rot);
    auto v = Vector3Transform((Vector3){0,0,speed*dt}, transform);
    pos +=v;
}
