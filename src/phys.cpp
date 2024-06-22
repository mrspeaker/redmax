#import <phys.hpp>

void rm::phys::integrate(float dt, rm::trans *t) {
    vel.x += 0.1 * dt;
    t->pos.x += vel.x;
    t->pos.x += vel.y;
    t->pos.z += vel.z;
};
