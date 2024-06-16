#include <raylib-cpp.hpp>
#include <globals.hpp>
#include <renderer.hpp>
#include <raylib-cpp.hpp>
#include <game_manager.hpp>
#include <iostream>

# define RLIGHTS_IMPLEMENTATION
# include "./rlights.h"

int main() {

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    raylib::Window w(screenWidth, screenHeight, "RedMax");

    rm::renderer rend{};
    rm::game_manager gm{};

    raylib::Shader shader("res/lighting.vs", "res/lighting.fs");

    /*auto ambientLoc = GetShaderLocation(shader, "ambient");
    std::cout<<ambientLoc<<"\n";
    float v[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
    SetShaderValue(shader, ambientLoc, v, SHADER_UNIFORM_VEC4);*/

    for (int i = 0; i < rend.plane.materialCount; i++) {
        rend.plane.materials[i].shader = shader;
    }
    for (int i = 0; i < rend.copse.materialCount; i++) {
        rend.copse.materials[i].shader = shader;
    }
    for (int i = 0; i < rend.tower.materialCount; i++) {
        rend.tower.materials[i].shader = shader;
    }
    for (int i = 0; i < rend.mountain.materialCount; i++) {
        rend.mountain.materials[i].shader = shader;
    }

    auto light = CreateLight(
                             LIGHT_DIRECTIONAL,
                             (Vector3){ -50.0, 100, 0 },
                             Vector3Zero(),
                             WHITE,
                             shader);

    w.SetTargetFPS(60);
    while (!w.ShouldClose()) {
        auto dt = GetFrameTime();
        gm.update(dt);

        //light.position.x = gm.plane.pos.x;
        //light.position.z = gm.plane.pos.z;
        //UpdateLightValues(shader, light);

        rend.render(gm, dt, shader);

    }
    return 0;
}
