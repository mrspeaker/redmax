#include <godzilla.hpp>

void rm::godzilla::update() {
    float sp = 0.02;
    auto a = t.rot.y * DEG2RAD;
    t.pos.x += std::sinf(a) * sp;
    t.pos.z += std::cosf(a) * sp;
}
