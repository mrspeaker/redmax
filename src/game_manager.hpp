#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <plane.hpp>
#include <tower.hpp>
#include <camera.hpp>
#include <terrain.hpp>
#include <missile.hpp>
#include <godzilla.hpp>
#include <seed.hpp>
#include <vector>

namespace rm {

class game_manager {
 public:
    rm::plane plane;
    rm::camera camera;
    rm::terrain terrain;
    std::vector<rm::godzilla> godzillas;
    std::vector<rm::tower> towers;
    std::vector<rm::missile> missiles;
    std::vector<rm::seed> seeds;
    rm::tile* last_plane_tile;
    bool seeded;
    game_manager();
    void update(float dt);
};

} // namespace rm

#endif // GAME_MANAGER_HPP
