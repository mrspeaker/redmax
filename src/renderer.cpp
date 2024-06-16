#include <globals.hpp>
#include <renderer.hpp>
#include <game_manager.hpp>
#include <raylib-cpp.hpp>
#include <iostream>

rm::renderer::renderer() {
    text_col = raylib::Color::Black();
    plane = raylib::Model("res/biplane.glb");
    tower = raylib::Model("res/control.glb");
    copse = raylib::Model("res/copse.glb");
    mountain = raylib::Model("res/mountain.glb");

    //    shader = raylib::Shader("res/lighting.vs", "res/lighting.fs");
    //Light lights[MAX_LIGHTS] = { 0 };
    //lights[0] =mo
}

const Color pal[] ={BROWN, DARKBROWN, RED};

void rm::renderer::render(game_manager &gm, float dt, raylib::Shader &shader) {
    BeginDrawing();
    ClearBackground(BLACK);
    raylib::Color g(DARKGRAY);

    gm.camera.cam.BeginMode();

    // ground
    for (const auto ch : gm.terrain.chunks) {
        auto ch_pos = Vector3{
                ch.x * 100.0f,
                0,
                ch.z * 100.0f
        };
        DrawPlane(ch_pos, Vector2{ 99.0, 99.0 },
            pal[ch.col]);
    }

    shader.BeginMode();

    // ground
    for (const auto ch : gm.terrain.chunks) {
        auto ch_pos = Vector3{
                ch.x * 100.0f,
                0,
                ch.z * 100.0f
        };
        for (const auto p : ch.trees) {
            copse.Draw(Vector3Add(ch_pos,p), 1.0f, RAYWHITE);
        }
    }

    mountain.Draw(Vector3{0.0, 1.0, 200.0}, 1.0f, RAYWHITE);

    plane.transform = gm.plane.transform;

    // shadow
    plane.Draw(Vector3{gm.plane.pos.x, 0.0, gm.plane.pos.z}, 1.0f, BLACK);
    plane.Draw(gm.plane.pos, 1.0f, RAYWHITE);

    // towers
    for (const auto &t : gm.towers) {
        tower.Draw(t.pos, 1.0f, RAYWHITE);
    }

    shader.EndMode();
    gm.camera.cam.EndMode();

    // ui
    text_col.DrawText(TextFormat("sp: %.2f", gm.plane.speed), 10, 10, 12);
    text_col.DrawText(TextFormat("alt: %.2f", gm.plane.pos.y), 10, 20, 12);

    EndDrawing();
};
