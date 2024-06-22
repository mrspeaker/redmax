#include <missile.hpp>

bool rm::missile::update(float dt) {
    if (target != nullptr) {
        raylib::Vector2 p1 = {t.pos.z, t.pos.x};
        raylib::Vector2 p2 = {target->z, target->x};
        auto a = p1.Angle(p2);
        if (a > t.rot.y) t.rot.y += 1.0 * dt;
        if (a < t.rot.y) t.rot.y -= 1.0 * dt;

        auto sp = 2.0 * dt;
        if (t.pos.y < target->y) t.pos.y+=sp;
        if (t.pos.y > target->y) t.pos.y-=sp;
    }
    phys.integrate(dt, &t);


    life -= dt;
    return life < 0.0;
}
