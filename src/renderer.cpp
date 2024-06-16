#include <globals.hpp>
#include <renderer.hpp>
#include <game_manager.hpp>
#include <raylib-cpp.hpp>
#include <iostream>

Matrix toMatrix(Vector3 pos, Quaternion rot, Vector3 scale) {
    return Matrix();
}

rm::renderer::renderer() {
    text_col = raylib::Color::Black();
    plane = raylib::Model("res/biplane.glb");
    tower = raylib::Model("res/control.glb");
}

void rm::renderer::render(game_manager &gm, float dt) {
    BeginDrawing();
    ClearBackground(BLACK);
    raylib::Color g(DARKGRAY);

    gm.camera.cam.BeginMode();

    // ground
    DrawPlane(Vector3{0,0,0}, Vector2{ 1000.0, 1000.0 }, DARKBROWN);

    plane.transform = gm.plane.transform;

    // shadow
    plane.Draw(Vector3{gm.plane.pos.x, 0.0, gm.plane.pos.z}, 1.0f, BLACK);
    plane.Draw(gm.plane.pos, 1.0f, RAYWHITE);

    // towers
    for (const auto &t : gm.towers) {
        tower.Draw(t.pos, 1.0f, RAYWHITE);
    }

    gm.camera.cam.EndMode();

    // ui
    text_col.DrawText(TextFormat("sp: %.2f", gm.plane.speed), 10, 10, 12);
    text_col.DrawText(TextFormat("alt: %.2f", gm.plane.pos.y), 10, 20, 12);

    EndDrawing();
};
