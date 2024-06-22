#import <phys.hpp>

rm::phys::phys()
    :vel{0,0,0}
    ,acc{0,0,0}{};


void rm::phys::integrate(float dt, rm::trans *t) {
    vel = vel.Add(acc.Scale(dt));

    t->pos.x += vel.x;
    t->pos.x += vel.y;
    t->pos.z += vel.z;
};
