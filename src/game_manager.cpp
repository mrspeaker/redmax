#include <game_manager.hpp>
#include <iostream>
#include <raylib-cpp.hpp>
#include <godzilla.hpp>

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

    for (int j = 0; j < 20; j++) {
        auto g = rm::godzilla{};
        g.t.pos.x = GetRandomValue(-100, 100) * 1.0f;
        g.t.pos.z = GetRandomValue(-100, 100) * 1.0f;
        g.t.pos.y = 0.0;
        g.t.rot.y = (j / 20.f) * 360.f;//(GetRandomValue(0, 100) / 100.0f) * 360.0f;
        godzillas.push_back(g);
    }


    auto m = rm::missile();
    m.t.pos.z = 3.0f;
    m.t.pos.x = 20.0f;
    missiles.push_back(m);
};

void rm::game_manager::update(float dt) {
    auto xo = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
    auto yo = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

    auto is_left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || xo < -0.5;
    auto is_right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) || xo > 0.5;
    auto is_up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || yo < -0.5;
    auto is_down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || yo > 0.5;

    auto is_action = IsKeyDown(KEY_SPACE);

    plane.update(dt, is_left, is_right, is_up, is_down);

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

    for (auto& g : godzillas) {
        g.update();
    }


    for (auto& ch : terrain.chunks) {
        ch.update();
    }

    for (auto& m : missiles) {
        m.update();
    }

    if (is_action) {
        auto t = terrain.get_tile_from_pos(plane.pos.x, plane.pos.z);
        t->next_type = 2;
    }
}
