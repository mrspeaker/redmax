#include <globals.hpp>
#include <renderer.hpp>
#include <game_manager.hpp>
#include <raylib-cpp.hpp>
#include <iostream>

#define RLIGHTS_IMPLEMENTATION
#include "./rlights.h"

rm::renderer::renderer(game_manager &gm)
    : window(screenWidth, screenHeight, "RedMax"),
      text_col(raylib::Color::White()),
      plane("res/biplane.glb"),
      tower("res/control.glb"),
      runman("res/runman.glb"),
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
    for (int i = 0; i < runman.materialCount; i++) {
        runman.materials[i].shader = light_shader;
    }
    for (int i = 0; i < mountain.materialCount; i++) {
        mountain.materials[i].shader = light_shader;
    }
    for (int i = 0; i < mygod.materialCount; i++) {
        mygod.materials[i].shader = light_shader;
    }

    anims = raylib::ModelAnimation::Load("res/runman.glb");

    Texture2D tex = LoadTexture("res/terrain.png");
    mountain.materials[1].maps[0].texture = tex;

    /*auto ambientLoc = GetShaderLocation(light_shader, "ambient");
    float v[4] = { 0.0f, 150.0f,250.0f, 1.0f };
    SetShaderValue(light_shader, ambientLoc, v, SHADER_UNIFORM_VEC4);*/

    // Generate tilemap as image
    int width = 16;
    int height = 16;
    pixels = new Color[width * height];

    /* for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if ((x+y)%2 == 0) pixels[y*width + x] = Color{0*16,0*16,0};
            else pixels[y*width + x] = Color{
                    static_cast<unsigned char>(GetRandomValue(0,4)*16),
                   static_cast<unsigned char>(GetRandomValue(0,4)*16),
                    0};
        }
        }*/
    Image tileMapIm = {
        .data = pixels,
        .width = width,
        .height = height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    Texture2D checked = LoadTextureFromImage(tileMapIm);
    //UnloadImage(tileMapIm);


    auto light_color =  Color{190,90,150};
    light = CreateLight(
                        LIGHT_DIRECTIONAL,
                        (Vector3){ -50.0, 100, 0 },
                        Vector3Zero(),
                        light_color,
                        light_shader);

    CreateLight(
                        LIGHT_DIRECTIONAL,
                        (Vector3){ -50.0, 100, 0 },
                        Vector3Zero(),
                        light_color,
                        tile_shader);

    window.SetTargetFPS(60);

    auto size = 2;
    auto resZ = size + 1;
    auto resX = size + 1;

    auto mesh = GenMeshPlane(gm.terrain.chunk_size, gm.terrain.chunk_size, size, size);

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
    auto ii = 0;
    auto size = gm.terrain.chunk_size;
    for (auto ch : gm.terrain.chunks) {
        if (!ch.dirty) continue;
        ch.dirty = false;
        auto ch_pos = Vector3{ch.x * size + size / 2.0f, 0, ch.z * size + size / 2.0f};

        // todo: do this better. Currently updating the texture each time before
        // drawing (even for non-visible chunks!).
        // Should have a screen full of grid models, each with a texture...
        // and even then only update if chunk is dirty
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Color c{};
                auto& tile = ch.tiles[y * width + x];
                switch(tile.type) {
                case 0:
                    c = Color{5 * 16, 2 * 16, 0};
                    break;
                case 1:
                    c = Color{3 * 16, 1 * 16, 0};
                    break;
                case 2:
                    c = Color{static_cast<unsigned char>((tile.ticks / 100) * 16), 15 * 16, 0};
                    break;
                case 3:
                    c = Color{0 * 16, 0 * 16, 0};
                    break;
                default:
                    c = Color{3 * 16, 2 * 16, 0};
                }
                pixels[y * width + x] = c;
            }
        }
        UpdateTexture(grid.materials[0].maps[MATERIAL_MAP_SPECULAR].texture, pixels);

        grid.Draw(ch_pos, 1.0f, pal[ch.col]);

        for (const auto p : ch.trees) {
            copse.Draw(Vector3Add(ch_pos,p), 1.0f, RAYWHITE);
        }
    }

    /*   if (GetRandomValue(0, 100) == 1) {
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
        }*/

    mountain.Draw(Vector3{0.0, 1.0, 200.0}, 1.0f, RAYWHITE);

    for (auto& g : gm.godzillas) {
        mygod.Draw(
               g.t.pos,
               Vector3{0.0f, 1.0f, 0.0},
               g.t.rot.y,
               Vector3{2.0,2.0,2.0}, RAYWHITE);
    }

    plane.transform = gm.plane.t.transform;

    // shadow
    plane.Draw(Vector3{gm.plane.t.pos.x, 0.0, gm.plane.t.pos.z}, 0.8f, BLACK);
    plane.Draw(gm.plane.t.pos, 1.0f, RAYWHITE);

    // towers
    for (const auto &t : gm.towers) {
        tower.Draw(t.pos, 1.0f, RAYWHITE);
    }

    // missiles
    for (const auto &m : gm.missiles) {
        m.t.pos.DrawCube(2.0f, 2.0f, 2.0f, YELLOW);
    }

    // pickups
    for (const auto &p : gm.pickups) {
        auto c = WHITE;
        if (p.type == rm::item_type::GRASS) c = GREEN;
        if (p.type == rm::item_type::TURRET) c = RED;
        p.t.pos.DrawCube(2.0f, 2.0f, 2.0f, c);
    }

    runman.UpdateAnimation(anims[0], frame++);
    runman.Draw(raylib::Vector3(30.0, 0.0, 64.0), 3.0f, BLUE);
    runman.Draw(raylib::Vector3(40.0, 0.0, 64.0), 3.0f, BLUE);

    // seeds
    for (const auto &s : gm.seeds) {
        auto c = WHITE;
        if (s.type == rm::item_type::GRASS) c = GREEN;
        if (s.type == rm::item_type::TURRET) c = RED;
        s.t.pos.DrawCube(1.0f, 1.0f, 1.0f, c);
    }

    gm.camera.cam.EndMode();

    auto x = gm.plane.t.pos.x;
    auto y = gm.plane.t.pos.z;
    auto chunk_x = static_cast<int>(std::floor((x + 0.0) / size));
    auto chunk_y = static_cast<int>(std::floor((y + 0.0) / size));
    auto chunk_idx = (chunk_y + 4) * 9 + (chunk_x + 4);

    // ui
    text_col.DrawText(TextFormat("sp: %.2f", gm.plane.speed), 10, 10, 12);
    text_col.DrawText(TextFormat("alt: %.2f", gm.plane.t.pos.y), 10, 20, 12);
    text_col.DrawText(TextFormat("pos: %.2f %.2f", gm.plane.t.pos.x, gm.plane.t.pos.z), 10, 30, 12);
    text_col.DrawText(TextFormat("chk: %d %d %d", chunk_x, chunk_y, chunk_idx), 10, 40, 12);

    for(int i = 0; i < rm::inventory::MAX_SLOTS; i++) {
        text_col.DrawText(TextFormat("%d: %d", i + 1, gm.inv.slots[i].num), 100, 100 + i * 20,
                          i == gm.inv.cur_slot ? 14 : 10);
    }

    EndDrawing();
};
