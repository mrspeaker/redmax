#include <seed.hpp>

void rm::seed::update(float dt) {
    t.pos.y -= 10.0 * dt;
    if (t.pos.y <= 0.0) {
        state = rm::seed_state::LANDED;
    }
}
