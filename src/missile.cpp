#include <missile.hpp>

rm::missile::missile()=default;

bool rm::missile::update(float dt) {
    phys.integrate(dt, &t);
    if (t.pos.x > 400.0) { t.pos.x = -400.0; }
    life -= dt;
    return life < 0.0;
}
