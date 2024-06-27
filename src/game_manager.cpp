#include <game_manager.hpp>
#include <godzilla.hpp>
#include <vector>
#include <algorithm>

void rm::game_manager::on_notify(game_event event, float x, float y, float z) {
    switch(event) {
    case game_event::SPAWN:
        auto p = rm::pickup(GetRandomValue(0, 2) == 0 ? item_type::GRASS : item_type::TURRET);
        p.t.pos.x = x;
        p.t.pos.y = 1.5;
        p.t.pos.z = z;
        pickups.push_back(p);
        break;
    }
}

rm::game_manager::game_manager():terrain(128.0), inv{} {
    plane.t.pos.x += 20.0;

    // some towers
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 4; i++) {
            rm::tower t{};
            t.pos.y = 0.1f;
            t.pos.x = (j - 1) * 180.0f;
            t.pos.z = (i - 2) * 185.0f;
            towers.push_back(t);
        }
    }

    // Hook up observers for tile events
    for (auto& ch : terrain.chunks) {
        ch.add_observer(this);
    }

    // Some godzillas
    for (int j = 0; j < 20; j++) {
        auto g = rm::godzilla{};
        g.t.pos.x = GetRandomValue(-400, 400) * 1.0f;
        g.t.pos.z = GetRandomValue(-400, 400) * 1.0f;
        g.t.pos.y = 0.0;
        g.t.rot.y = (j / 20.f) * 360.f;
        godzillas.push_back(g);
    }

    // pickup for seeds
    auto p = rm::pickup(rm::item_type::GRASS);
    p.t.pos.x = 64.0;
    p.t.pos.z = 64.0;
    p.t.pos.y = 14.0;
    pickups.push_back(p);

    p = rm::pickup(rm::item_type::TURRET);
    p.t.pos.x = 96.0;
    p.t.pos.z = 96.0;
    p.t.pos.y = 14.0;
    pickups.push_back(p);

    for (int i = 0; i < 20; i++) {
        auto p = rm::peep{};
        p.t.pos.x = GetRandomValue(-50, 50) * 1.0f;
        p.t.pos.z = GetRandomValue(-50, 50) * 1.0f;
        p.t.pos.y = 0.0;
        p.t.rot.y = GetRandomValue(0, 360) * DEG2RAD;
        peeps.push_back(p);
    }

};

void rm::game_manager::update(float dt) {
    auto xo = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
    auto yo = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

    auto is_left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || xo < -0.5;
    auto is_right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) || xo > 0.5;
    auto is_up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || yo < -0.5;
    auto is_down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || yo > 0.5;
    if (IsKeyDown(KEY_ONE)) inv.cur_slot = 0;
    if (IsKeyDown(KEY_TWO)) inv.cur_slot = 1;

    auto is_action = IsKeyDown(KEY_SPACE);

    plane.update(dt, is_left, is_right, is_up, is_down);
    auto& pos = plane.t.pos;

    // What tile are we over?
    auto tile = terrain.get_tile_from_pos(pos.x, pos.z);
    if (tile != last_plane_tile) {
        seeded = false;
        last_plane_tile = tile;
    }

    // Wrap plane "seamlessly"
    const auto size = 300.0;
    if (pos.x < -size) pos.x += size * 2.0;
    if (pos.x > size) pos.x -= size * 2.0;
    if (pos.z < -size) pos.z += size * 2.0;
    if (pos.z > size) pos.z -= size * 2.0;

    // Cam update
    camera.cam.position.x = pos.x;
    camera.cam.position.z = pos.z - 50;
    auto cyo = (std::clamp(pos.y, 20.0f, 50.0f) - 20.0f) / 30.0f;
    camera.cam.position.y = (plane.speed + 10) / 50.0 * (100.0 + cyo * 200.0);
    camera.cam.target.x = pos.x;
    camera.cam.target.z = pos.z;

    // Peeps
    for (auto& p : peeps) {
        p.update(dt);
    }

    // Godzillaz
    for (auto& g : godzillas) {
        g.update(dt);
        auto dist = g.t.pos.Distance(pos);
        if (dist < 100.0f && g.can_fire()) {
            g.fire();
            auto m = rm::missile(&pos);
            m.t.pos.x = g.t.pos.x;
            m.t.pos.y = 10.0f;
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

    // cellular automata updates
    terrain.update(dt);

    // missiles
    std::erase_if(missiles, [&](rm::missile& m) {
        auto alive = m.update(dt);
        auto dist = m.t.pos.Distance(pos);
        if (dist < 6.0) {
            // hit plane.
            return true;
        }
        return alive;
    });

    // pickups
    auto plane_xz = raylib::Vector2(pos.x, pos.z);
    std::erase_if(pickups, [&](rm::pickup& p) {
        auto xz_dist = raylib::Vector2(p.t.pos.x, p.t.pos.z).Distance(plane_xz);
        if (xz_dist < 5.0f && std::fabs(pos.y - p.t.pos.y) < 20.0) {
            inv.add_item(p.type, 2);
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
            if (s.type == item_type::GRASS) {
                if (t->type != 2 && t->type != 3) {
                    t->next_type = 2;
                }
            }
            if (s.type == item_type::TURRET) {
                t->next_type = 1;
                // Spawn turret.
            }
        }
        return landed;
    });

    // Fire seeds, if you gottem
    if (is_action && inv.slots[inv.cur_slot].num > 0 && plane.flying() && !seeded) {
        seeded = true;
        inv.slots[inv.cur_slot].num-=1;
        auto seed = rm::seed();
        seed.type = inv.slots[inv.cur_slot].type;
        seed.t.pos.x = pos.x;
        seed.t.pos.y = pos.y;
        seed.t.pos.z = pos.z;
        seeds.push_back(seed);
    }
}
