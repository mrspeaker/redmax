#include <plane.hpp>

#include <raylib-cpp.hpp>

rm::plane::plane() {
    speed = 0.0;
}

void rm::plane::update(float dt, bool is_left, bool is_right, bool is_up, bool is_down) {

    const auto rot_speed = 2.5f * dt;
    const auto max_speed = 40.0;
    const auto takeoff_speed = 15.0;
    const auto acceleration = 10.0;
    const auto lift_speed = 15.0;
    const auto ground_friction = 0.95;

    auto yaw = rot.y;
    auto roll = rot.z;

    auto yawo = 0.0;
    if (is_left) yawo += rot_speed;
    else if (is_right) yawo -= rot_speed;

    yaw += yawo;

    const auto roll_speed = 0.5f;
    const auto max_roll = 75 * DEG2RAD;
    if (yawo > 0) {
        if (roll > -max_roll) {
            roll -= (roll_speed * roll > 0 ? 2 : 1) * dt;
        }
    }
    else if (yawo < 0) {
        if (roll < max_roll) {
            roll += (roll_speed * roll < 0 ? 2 : 1) * dt;
        }
    }
    else {
        if (roll > 0.0f) roll -= 0.5f * dt;
        else if (roll < 0.0f) roll += 0.5f * dt;
    }

    rot.y = yaw;
    rot.z = roll;

    const auto ground = 1.5;

    const auto flying = pos.y > ground;
    const auto falling = flying && speed < takeoff_speed;

    const auto is_control = is_down || is_up;

    if (is_down) {
            speed += acceleration * dt;
        if (speed > takeoff_speed) {
            pos.y += lift_speed * dt;
        }
    }

    if (is_up || falling) {
        if (flying) {
            speed -= acceleration * 0.5 * dt;
            pos.y -= lift_speed * dt;
        } else {
            speed -= acceleration * dt;
        }
    }

    if (!flying && !is_control) {
        speed *= ground_friction;
    }
    if (flying && !falling && !is_control) {
        speed += acceleration * dt;
    }

    if (pos.y <= ground) pos.y = ground;
    if (speed <= 0.0) speed = 0.0;
    if (falling && speed < 5.0) speed = 10.0;
    if (speed >= max_speed) speed = max_speed;

    auto vel = speed;
    if (falling && speed < takeoff_speed) vel = takeoff_speed;

    transform = raylib::Matrix().RotateXYZ(rot);
    auto v = Vector3Transform((Vector3){0,0,vel*dt}, transform);
    pos +=v;
}

bool rm::plane::flying() {
    const auto ground = 1.5;

    return pos.y > ground;
}
