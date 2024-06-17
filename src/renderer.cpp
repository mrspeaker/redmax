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

    auto mesh = GenMeshPlane(100.0, 100.0, 16, 16);
    /*for (int z = 1; z < 9; z++) {
        for (int x = 1; x < 9; x++) {
            mesh.vertices[(z * 10 + x) * 3 + 1] += GetRandomValue(-20, 20) / 5.0;
        }
    }
    UpdateMeshBuffer(
                     mesh,
                     0,
                     mesh.vertices,
                     mesh.vertexCount*3*sizeof(float),
                     0);*/

    auto resZ = 17;
    auto resX = 17;
    for (int v = 0; v < resZ; v++) {
        for (int u = 0; u < resX; u++) {
            int i = (v * resZ + u) * 2;
            int uu = u % 3;
            int vv = v % 3;
            mesh.texcoords[i] = (float)uu/(resX - 1);
            mesh.texcoords[i + 1] = (float)vv/(resZ - 1);
        }
    }

    UpdateMeshBuffer(
                     mesh,
                     1,
                     mesh.texcoords,
                     mesh.vertexCount*2*sizeof(float),
                     0);

    grid = LoadModelFromMesh(mesh);
}

const Color pal[] ={BROWN, DARKBROWN, WHITE, DARKGREEN};

void rm::renderer::render(game_manager &gm, float dt, raylib::Shader &shader) {
    BeginDrawing();
    ClearBackground(BLACK);
    raylib::Color g(DARKGRAY);

    gm.camera.cam.BeginMode();

    shader.BeginMode();

    // ground
    for (const auto ch : gm.terrain.chunks) {
        auto ch_pos = Vector3{
                ch.x * 100.0f,
                0,
                ch.z * 100.0f
        };
        grid.Draw(ch_pos, 1.0f, pal[ch.col]);
        for (const auto p : ch.trees) {
            copse.Draw(Vector3Add(ch_pos,p), 1.0f, RAYWHITE);
        }
    }

    mountain.Draw(Vector3{0.0, 1.0, 200.0}, 1.0f, RAYWHITE);

    plane.transform = gm.plane.transform;

    // shadow
    plane.Draw(Vector3{gm.plane.pos.x, 0.0, gm.plane.pos.z}, 0.8f, BLACK);
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
