#include <raylib-cpp.hpp>
#include <globals.hpp>
#include <renderer.hpp>
#include <raylib-cpp.hpp>
#include <game_manager.hpp>

int main() {
    raylib::Window w(screenWidth, screenHeight, "RedMax");

    rm::renderer rend{};
    rm::game_manager gm{};

    w.SetTargetFPS(60);
    while (!w.ShouldClose())
    {
        auto dt = GetFrameTime();
        gm.update(dt);

        rend.render(gm, dt);
    }

    return 0;
}
