#import <phys.hpp>

rm::phys::phys()
    :vel{0,0,0}
    ,acc{0,0,0}{};


void rm::phys::integrate(float dt, rm::trans *t) {
    //vel = vel.Add(acc.Scale(dt));
    vel.z += acc.z * dt;
    t->pos.x += std::sinf(t->rot.y) * vel.z;
    t->pos.y += vel.y;
    t->pos.z += std::cosf(t->rot.y) * vel.z;
};
