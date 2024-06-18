#ifndef RENDERER_RAYLIB_H
#define RENDERER_RAYLIB_H

#include <raylib-cpp.hpp>
#include <game_manager.hpp>
#include "./rlights.h"

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
    Light light;

    raylib::Shader light_shader;
    raylib::Shader tile_shader;

    renderer();
    void render(rm::game_manager &gm);
};

} // namespace rm

#endif // RENDERER_H
