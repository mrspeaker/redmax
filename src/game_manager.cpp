#include "Vector2.hpp"
#include <game_manager.hpp>
#include <iostream>
#include <raylib-cpp.hpp>
#include <godzilla.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

void rm::game_manager::on_notify(game_event event, float x, float y, float z) {
    switch(event) {
    case game_event::SPAWN:
        auto p = rm::pickup();
        p.t.pos.x = x;
        p.t.pos.y = 1.5;
        p.t.pos.z = z;
        pickups.push_back(p);
        break;
    }
}

rm::game_manager::game_manager():terrain(128.0) {
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 4; i++) {
            rm::tower t{};
            t.pos.y = 0.1f;
            t.pos.x = (j - 1) * 180.0f;
            t.pos.z = (i - 2) * 185.0f;
            towers.push_back(t);
        }
    }
    plane.pos.x += 20.0;

    // Hook up observers
    for (auto& ch : terrain.chunks) {
        ch.add_observer(this);
    }

    for (int j = 0; j < 20; j++) {
        auto g = rm::godzilla{};
        g.t.pos.x = GetRandomValue(-400, 400) * 1.0f;
        g.t.pos.z = GetRandomValue(-400, 400) * 1.0f;
        g.t.pos.y = 0.0;
        g.t.rot.y = (j / 20.f) * 360.f;
        godzillas.push_back(g);
    }

    auto p = rm::pickup();
    p.t.pos.x = 64.0;
    p.t.pos.z = 64.0;
    p.t.pos.y = 14.0;
    pickups.push_back(p);


};

void rm::game_manager::update(float dt) {
    auto xo = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
    auto yo = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

    auto is_left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || xo < -0.5;
    auto is_right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) || xo > 0.5;
    auto is_up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || yo < -0.5;
    auto is_down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || yo > 0.5;

    auto is_action = IsKeyDown(KEY_SPACE);

    plane.update(dt, is_left, is_right, is_up, is_down);
    auto tile = terrain.get_tile_from_pos(plane.pos.x, plane.pos.z);
    if (tile != last_plane_tile) {
        seeded = false;
        last_plane_tile = tile;
    }

    const auto size = 300.0;
    if (plane.pos.x < -size) plane.pos.x += size * 2.0;
    if (plane.pos.x > size) plane.pos.x -= size * 2.0;
    if (plane.pos.z < -size) plane.pos.z += size * 2.0;
    if (plane.pos.z > size) plane.pos.z -= size * 2.0;

    camera.cam.position.x = plane.pos.x;
    camera.cam.position.z = plane.pos.z - 50;
    auto cyo = (std::clamp(plane.pos.y, 20.0f, 50.0f) - 20.0f) / 30.0f;
    camera.cam.position.y = (plane.speed + 10) / 50.0 * (100.0 + cyo * 200.0);
    camera.cam.target.x = plane.pos.x;
    camera.cam.target.z = plane.pos.z;

    for (auto& g : godzillas) {
        g.update(dt);
        auto dist = g.t.pos.Distance(plane.pos);
        if (dist < 100.0f && g.can_fire()) {
            g.cooldown = 0;
            auto m = rm::missile(&plane.pos);
            m.t.pos.x = g.t.pos.x;
            m.t.pos.y = 1.0f;
            m.t.pos.z = g.t.pos.z;
            m.phys.acc.z = 0.1f;
            m.t.rot.y = 0.0f;
            m.life = 10.0;
            missiles.push_back(m);
        }
        if (g.t.pos.x < -400.0) g.t.pos.x += 800.0;
        if (g.t.pos.x > 400.0) g.t.pos.x -= 800.0;
        if (g.t.pos.z < -400.0) g.t.pos.z += 800.0;
        if (g.t.pos.z > 400.0) g.t.pos.z -= 800.0;
    }

    terrain.update(dt);

    // missiles
    std::erase_if(missiles, [&](rm::missile& m) {
        auto alive = m.update(dt);
        auto dist = m.t.pos.Distance(plane.pos);
        if (dist < 6.0) {
            // hit plane.
            return true;
        }
        return alive;
    });

    // pickups
    auto plane_xz = raylib::Vector2(plane.pos.x, plane.pos.z);
    std::erase_if(pickups, [&](rm::pickup& p) {
        auto xz_dist = raylib::Vector2(p.t.pos.x, p.t.pos.z).Distance(plane_xz);
        if (xz_dist < 5.0f && std::fabs(plane.pos.y - p.t.pos.y) < 20.0) {
            inv.add_item(slot_type::SEEDS, 5);
            return true;
        }
        return false;
    });

    // Plant seeds if they hit the deck
    std::erase_if(seeds, [&](rm::seed& s) {
        s.update(dt);
        auto landed = s.state == rm::seed_state::LANDED;
        if (landed) {
            auto t = terrain.get_tile_from_pos(s.t.pos.x, s.t.pos.z);
            if (t->type != 2 && t->type != 3) {
                t->next_type = 2;
            }
        }
        return landed;
    });

    // Fire seeds
    if (is_action && inv.slots[0].num > 0 && plane.flying() && !seeded) {
        seeded = true;
        inv.slots[0].num-=1;
        auto seed = rm::seed();
        seed.t.pos.x = plane.pos.x;
        seed.t.pos.y = plane.pos.y;
        seed.t.pos.z = plane.pos.z;
        seeds.push_back(seed);
    }
}
