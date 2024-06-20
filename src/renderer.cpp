#include <globals.hpp>
#include <renderer.hpp>
#include <game_manager.hpp>
#include <raylib-cpp.hpp>
#include <iostream>

#define RLIGHTS_IMPLEMENTATION
#include "./rlights.h"

rm::renderer::renderer()
    : window(screenWidth, screenHeight, "RedMax"),
      text_col(raylib::Color::Black()),
      plane("res/biplane.glb"),
      tower("res/control.glb"),
      copse("res/copse.glb"),
      mountain("res/mountain.glb"),
      mygod("res/mygod.glb"),
      light_shader("res/lighting.vs", "res/lighting.fs"),
      tile_shader("res/lighting.vs", "res/tiles.fs"),
      godzilla("res/godzilla.png") {

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

    /*auto ambientLoc = GetShaderLocation(light_shader, "ambient");
    float v[4] = { 0.0f, 150.0f,250.0f, 1.0f };
    SetShaderValue(light_shader, ambientLoc, v, SHADER_UNIFORM_VEC4);*/

    // Generate tilemap as image
    int width = 16;
    int height = 16;
    pixels = new Color[width * height];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if ((x+y)%2 == 0) pixels[y*width + x] = Color{0*16,0*16,0};
            else pixels[y*width + x] = Color{
                    static_cast<unsigned char>(GetRandomValue(0,4)*16),
                   static_cast<unsigned char>(GetRandomValue(0,4)*16),
                    0};
        }
    }
    Image tileMapIm = {
        .data = pixels,
        .width = width,
        .height = height,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1
    };
    Texture2D checked = LoadTextureFromImage(tileMapIm);
    //UnloadImage(tileMapIm);


    light = CreateLight(
                        LIGHT_DIRECTIONAL,
                        (Vector3){ -50.0, 100, 0 },
                        Vector3Zero(),
                        WHITE,
                        light_shader);

    CreateLight(
                        LIGHT_DIRECTIONAL,
                        (Vector3){ -50.0, 100, 0 },
                        Vector3Zero(),
                        WHITE,
                        tile_shader);

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
    grid.materials[0].shader = tile_shader;
    grid.materials[0].maps[0].texture = tex;
    grid.materials[0].maps[MATERIAL_MAP_SPECULAR].texture = checked;
}

const Color pal[] ={BROWN, DARKBROWN, WHITE, DARKGREEN};

void rm::renderer::render(game_manager &gm) {
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
        grid.Draw(ch_pos, 1.0f, pal[ch.col]);

        for (const auto p : ch.trees) {
            copse.Draw(Vector3Add(ch_pos,p), 1.0f, RAYWHITE);
        }
    }

    if (GetRandomValue(0, 100) == 1) {
        auto height = 16;
        auto width = 16;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                pixels[y*width + x] = Color{
                    static_cast<unsigned char>(GetRandomValue(0,2)*16),
                    static_cast<unsigned char>(GetRandomValue(0,2)*16),
                    0};
            }
        }
        auto tex = grid.materials[0].maps[MATERIAL_MAP_SPECULAR].texture;
        UpdateTexture(tex, pixels);
    }

    mountain.Draw(Vector3{0.0, 1.0, 200.0}, 1.0f, RAYWHITE);

    auto z = static_cast<float>(GetRandomValue(0, 100)) / 100.0f - 0.5f;
    auto rot = 45.0f;
    mygod.Draw(
               Vector3{40.0, z, 20.0},
               Vector3{0.0f, 1.0f, 0.0},
               rot,
               Vector3{2.0,2.0,2.0}, RAYWHITE);

    plane.transform = gm.plane.transform;

    // shadow
    plane.Draw(Vector3{gm.plane.pos.x, 0.0, gm.plane.pos.z}, 0.8f, BLACK);
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
