#include <globals.hpp>
#include <renderer.hpp>
#include <game_manager.hpp>
#include <raylib-cpp.hpp>
#include <iostream>

raylib::Vector3 toVec3(rm::Vector3 v) {
    return raylib::Vector3(v.x, v.y, v.z);
}

rm::renderer::renderer() {
    text_col = raylib::Color::Gray();
    plane = raylib::Model("res/biplane.glb");
    tower = raylib::Model("res/control.glb");
}

void rm::renderer::render(game_manager &gm) {
    BeginDrawing();
    ClearBackground(BLACK);
    raylib::Color g(DARKGRAY);
    text_col.DrawText("RedMax", 190, 200, 10);

    gm.camera.cam.BeginMode();

    plane.Draw(toVec3(gm.plane.pos), 1.0f, RAYWHITE);

    for (const auto &t : gm.towers) {
        tower.Draw(toVec3(t.pos), 1.0f, RAYWHITE);
    }


    gm.camera.cam.EndMode();

    EndDrawing();
};
