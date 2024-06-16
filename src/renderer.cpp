#include <globals.hpp>
#include <renderer.hpp>
#include <game_manager.hpp>
#include <raylib-cpp.hpp>
#include <iostream>

Matrix toMatrix(Vector3 pos, Quaternion rot, Vector3 scale) {
    return Matrix();
}

rm::renderer::renderer() {
    text_col = raylib::Color::Gray();
    plane = raylib::Model("res/biplane.glb");
    tower = raylib::Model("res/control.glb");
}

void rm::renderer::render(game_manager &gm, float dt) {
    BeginDrawing();
    ClearBackground(BLACK);
    raylib::Color g(DARKGRAY);
    text_col.DrawText("RedMax", 190, 200, 10);

    gm.camera.cam.BeginMode();


    DrawPlane(Vector3{0,0,0}, Vector2{ 1000.0, 1000.0 }, DARKBROWN);


    plane.transform = raylib::Matrix()
        .RotateXYZ(gm.plane.rot);

    // Arrgh! Ok, no. Need to have the MODEL matrix available to Plane.
    auto v = Vector3Transform((Vector3){0,0,gm.plane.speed*dt}, plane.transform);
    gm.plane.pos +=v;


    // plane.transform = toMatrix(gm.plane.pos, gm.plane.rot, gm.plane.scale);
    //    plane.transform = MatrixRotateXYZ((raylib::Vector3){ DEG2RAD*0.0, DEG2RAD*gm.plane.yaw, DEG2RAD*gm.plane.roll });
    plane.Draw(gm.plane.pos, 1.0f, RAYWHITE);

    for (const auto &t : gm.towers) {
        tower.Draw(t.pos, 1.0f, RAYWHITE);
    }


    gm.camera.cam.EndMode();

    EndDrawing();
};
