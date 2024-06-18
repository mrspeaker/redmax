#include <globals.hpp>
#include <raylib-cpp.hpp>
#include <renderer.hpp>
#include <game_manager.hpp>

int main() {
    rm::renderer rend{};
    rm::game_manager gm{};

    while (!rend.window.ShouldClose()) {
        auto dt = GetFrameTime();
        gm.update(dt);
        rend.render(gm);
    }
    return 0;
}
