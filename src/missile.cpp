#include <missile.hpp>

bool rm::missile::update(float dt) {
    if (target != nullptr) {
        raylib::Vector2 p1 = {t.pos.z, t.pos.x};
        raylib::Vector2 p2 = {target->z, target->x};
        auto a = p1.Angle(p2);
        auto rot_speed = 2.0f;
        if (a > t.rot.y) t.rot.y += rot_speed * dt;
        if (a < t.rot.y) t.rot.y -= rot_speed * dt;

        auto v_speed = 5.0 * dt;
        if (t.pos.y < target->y) t.pos.y+= v_speed;
        if (t.pos.y > target->y) t.pos.y-= v_speed;
    }
    phys.integrate(dt, &t);


    life -= dt;
    return life < 0.0;
}
