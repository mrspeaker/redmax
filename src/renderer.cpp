#include <globals.hpp>
#include <renderer.hpp>
#include <game_manager.hpp>
#include <raylib-cpp.hpp>

#define RLIGHTS_IMPLEMENTATION
#include "./rlights.h"

rm::renderer::renderer()
    : window(screenWidth, screenHeight, "RedMax"),
      text_col(raylib::Color::Black()),
      plane("res/biplane.glb"),
      tower("res/control.glb"),
      copse("res/copse.glb"),
      mountain("res/mountain.glb"),
      light_shader("res/lighting.vs", "res/lighting.fs") {

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    for (int i = 0; i < plane.materialCount; i++) {
        plane.materials[i].shader = light_shader;
    }
    for (int i = 0; i < copse.materialCount; i++) {
        copse.materials[i].shader = light_shader;
    }
    for (int i = 0; i < tower.materialCount; i++) {
        tower.materials[i].shader = light_shader;
    }
    for (int i = 0; i < mountain.materialCount; i++) {
        mountain.materials[i].shader = light_shader;
    }

    Texture2D tex = LoadTexture("res/terrain.png");

    mountain.materials[1].maps[0].texture = tex;

    /*auto ambientLoc = GetShaderLocation(shader, "ambient");
    std::cout<<ambientLoc<<"\n";
    float v[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    SetShaderValue(shader, ambientLoc, v, SHADER_UNIFORM_VEC4);*/

    auto light = CreateLight(
                             LIGHT_DIRECTIONAL,
                             (Vector3){ -50.0, 100, 0 },
                             Vector3Zero(),
                             WHITE,
                             light_shader);

    window.SetTargetFPS(60);

    auto size = 2;
    auto resZ = size + 1;
    auto resX = size + 1;

    auto mesh = GenMeshPlane(100.0, 100.0, size, size);

    /*    auto scale = 0.0; // amount to scale height offset by
    for (int z = 0; z < resZ; z++) {
        for (int x = 0; x < resX; x++) {
            mesh.vertices[(z * resZ + x) * 3 + 1] += GetRandomValue(-20, 20) * scale;
        }
    }

    UpdateMeshBuffer(
                     mesh,
                     0,
                     mesh.vertices,
                     mesh.vertexCount*3*sizeof(float),
                     0);

    for (int v = 0; v < resZ; v++) {
        for (int u = 0; u < resX; u++) {
            int i = (v * resZ + u) * 2;
            float uu = u % 3; //u % 2 == 0 ? 0 : 1;
            float vv = v % 3; // v % 2 == 0 ? 0 : 1;
            mesh.texcoords[i] = (float)uu/(resX - 1);
            mesh.texcoords[i + 1] = (float)vv/(resZ - 1);
        }
    }

    UpdateMeshBuffer(
                     mesh,
                     1,
                     mesh.texcoords,
                     mesh.vertexCount*2*sizeof(float),
                     0);*/

    grid = LoadModelFromMesh(mesh);
    grid.materials[0].shader = light_shader;
    grid.materials[0].maps[0].texture = tex;
}

const Color pal[] ={BROWN, DARKBROWN, WHITE, DARKGREEN};

void rm::renderer::render(game_manager &gm) {
    BeginDrawing();
    ClearBackground(BLACK);
    raylib::Color g(DARKGRAY);

    gm.camera.cam.BeginMode();

    light_shader.BeginMode();

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

    light_shader.EndMode();
    gm.camera.cam.EndMode();

    // ui
    text_col.DrawText(TextFormat("sp: %.2f", gm.plane.speed), 10, 10, 12);
    text_col.DrawText(TextFormat("alt: %.2f", gm.plane.pos.y), 10, 20, 12);

    EndDrawing();
};
