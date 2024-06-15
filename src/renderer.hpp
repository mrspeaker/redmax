#ifndef RENDERER_RAYLIB_H
#define RENDERER_RAYLIB_H

#include <raylib-cpp.hpp>
#include <game_manager.hpp>

namespace rm {

class renderer {
 public:
    raylib::Color text_col;    
    raylib::Model plane;
    raylib::Model tower;

    renderer();
    void render(rm::game_manager &gm);
};

} // namespace rm

#endif // RENDERER_H
