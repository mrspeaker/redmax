#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <plane.hpp>
#include <tower.hpp>
#include <camera.hpp>
#include <terrain.hpp>
#include <missile.hpp>
#include <godzilla.hpp>
#include <seed.hpp>
#include <pickup.hpp>
#include <inventory.hpp>
#include <vector>
#include <observer.hpp>

namespace rm {

class game_manager : observer {
 public:
    rm::plane plane;
    rm::camera camera;
    rm::terrain terrain;
    rm::inventory inv;
    std::vector<rm::godzilla> godzillas;
    std::vector<rm::tower> towers;
    std::vector<rm::missile> missiles;
    std::vector<rm::seed> seeds;
    std::vector<rm::pickup> pickups;
    rm::tile* last_plane_tile;
    bool seeded;
    game_manager();
    void update(float dt);
    virtual void on_notify(game_event event, float x, float y, float z);
};

} // namespace rm

#endif // GAME_MANAGER_HPP
