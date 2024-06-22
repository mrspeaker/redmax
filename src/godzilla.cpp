#include <godzilla.hpp>

void rm::godzilla::update(float dt) {
    float sp = 2.0f * dt;
    auto a = t.rot.y * DEG2RAD;
    t.pos.x += std::sinf(a) * sp;
    t.pos.z += std::cosf(a) * sp;
}
