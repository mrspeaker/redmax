#import <phys.hpp>

void rm::phys::integrate(float dt, rm::trans *t) {
    vel.x += acc.x * dt;
    vel.y += acc.y * dt;
    vel.z += acc.z * dt;

    t->pos.x += vel.x;
    t->pos.x += vel.y;
    t->pos.z += vel.z;
};
