#include <godzilla.hpp>

void rm::godzilla::update(float dt) {
    if (state == rm::godz_state::WALK) {
        float sp = 2.0f * dt;
        auto a = t.rot.y * DEG2RAD;
        t.pos.x += std::sinf(a) * sp;
        t.pos.z += std::cosf(a) * sp;
    } else {
        if (state_time > 4.0f) {
            state = rm::godz_state::WALK;
            state_time = 0;
            anim_frame = 0;
            anim_num = 1;
        }
    }

    cooldown += dt;
    state_time += dt;
}

bool rm::godzilla::can_fire() {
    return cooldown > 10.0;
}

void rm::godzilla::fire() {
    if (!can_fire()) return;
    cooldown = GetRandomValue(-3, 3);

    state = rm::godz_state::ROAR;
    state_time = 0.0;
    anim_frame = 0;
    anim_num = 0;
}
