#include <game_manager.hpp>
#include <iostream>
#include <raylib-cpp.hpp>

rm::game_manager::game_manager() {
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 4; i++) {
            rm::tower t{};
            t.pos.y = 0.1f;
            t.pos.x = (j - 1) * 30.0f;
            t.pos.z = (i - 2) * 45.0f + 25.0f;
            towers.push_back(t);
        }
    }
};

void rm::game_manager::update(float dt) {
    auto xo = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
    auto yo = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

    auto yaw = plane.rot.y;
    auto roll = plane.rot.z;

    const auto rot_speed = 1.0f * dt;
    auto yawo = 0.0;
    if (IsKeyDown(KEY_LEFT)||xo < -0.5) yawo += rot_speed;
    else if (IsKeyDown(KEY_RIGHT)||xo > 0.5) yawo -= rot_speed;

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

    plane.rot.y = yaw;
    plane.rot.z = roll;
    plane.speed = 20;
    //plane.pos.z += 20*
    camera.cam.position.x = plane.pos.x;
    camera.cam.position.z = plane.pos.z - 50;
    camera.cam.target.x = plane.pos.x;
    camera.cam.target.z = plane.pos.z;
}
