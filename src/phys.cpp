#import <phys.hpp>

void rm::phys::integrate(rm::trans *t) {
    vel.x += 0.001;
    t->pos.x += vel.x;
    t->pos.x += vel.y;
    t->pos.z += vel.z;
};
