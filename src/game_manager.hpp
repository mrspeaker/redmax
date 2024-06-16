#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <plane.hpp>
#include <tower.hpp>
#include <camera.hpp>
#include <terrain.hpp>
#include <vector>

namespace rm {

class game_manager {
 public:
    rm::plane plane;
    rm::camera camera;
    rm::terrain terrain;
    std::vector<rm::tower> towers;

    game_manager();
    void update(float dt);
};

} // namespace rm

#endif // GAME_MANAGER_HPP
