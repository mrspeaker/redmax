#include <game_manager.hpp>
#include <iostream>
#include <raylib-cpp.hpp>

rm::game_manager::game_manager() {
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 4; i++) {
            rm::tower t{};
            t.pos.y = 0.1f;
            t.pos.x = (j - 1) * 180.0f;
            t.pos.z = (i - 2) * 185.0f;
            towers.push_back(t);
        }
    }
    plane.pos.x += 20.0;
};

void rm::game_manager::update(float dt) {
    auto xo = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
    auto yo = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

    auto is_left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || xo < -0.5;
    auto is_right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) || xo > 0.5;
    auto is_up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || yo < -0.5;
    auto is_down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || yo > 0.5;

    auto is_action = IsKeyDown(KEY_SPACE);

    plane.update(dt, is_left, is_right, is_up, is_down, is_action);

    const auto size = 300.0;
    if (plane.pos.x < -size) plane.pos.x += size * 2.0;
    if (plane.pos.x > size) plane.pos.x -= size * 2.0;
    if (plane.pos.z < -size) plane.pos.z += size * 2.0;
    if (plane.pos.z > size) plane.pos.z -= size * 2.0;

    camera.cam.position.x = plane.pos.x;
    camera.cam.position.z = plane.pos.z - 50;
    camera.cam.position.y = (plane.speed + 10) / 30.0 * 200.0;
    camera.cam.target.x = plane.pos.x;
    camera.cam.target.z = plane.pos.z;

}
