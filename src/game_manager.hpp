#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <camera.hpp>
#include <godzilla.hpp>
#include <inventory.hpp>
#include <missile.hpp>
#include <observer.hpp>
#include <peep.hpp>
#include <plane.hpp>
#include <pickup.hpp>
#include <raylib-cpp.hpp>
#include <seed.hpp>
#include <tower.hpp>
#include <terrain.hpp>
#include <vector>

namespace rm {

enum class player_state {
    FLYING,
    LANDED,

};

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
    std::vector<rm::peep> peeps;

    rm::tile* last_plane_tile;
    bool seeded=false;

    rm::player_state player_state;

    game_manager();
    void update(float dt);
    virtual void on_notify(game_event event, float x, float y, float z);
};

} // namespace rm

#endif // GAME_MANAGER_HPP
