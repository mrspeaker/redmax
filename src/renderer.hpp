#ifndef RENDERER_RAYLIB_H
#define RENDERER_RAYLIB_H

#include <raylib-cpp.hpp>
#include <game_manager.hpp>
#include "./rlights.h"
#include <memory>

namespace rm {

class renderer {
public:
    raylib::Window window;
    raylib::Color text_col;    
    raylib::Model plane;
    raylib::Model tower;
    raylib::Model copse;
    raylib::Model mountain;
    raylib::Model grid;
    raylib::Model mygod;
    Light light;

    raylib::Shader light_shader;
    raylib::Shader tile_shader;

    raylib::Texture2D godzilla;

    Color *pixels;

    renderer(game_manager &gm);
    void render(rm::game_manager &gm);
    ~renderer() {
        delete[] pixels;
    }
};

} // namespace rm

#endif // RENDERER_H
