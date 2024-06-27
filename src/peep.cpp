#import <peep.hpp>

rm::peep::peep() {
    /* phys.acc.z = 0.05f;
    phys.integrate(1.0, &t);
    phys.acc.z = 0.0f;*/
}

void rm::peep::update(float dt) {
    if (state == peep_state::WALK) {
        anim_frame ++;
        phys.integrate(dt, &t);
        if (GetRandomValue(0, 80) == 1) {
            t.rot.y = t.rot.y + GetRandomValue(0, 45) * DEG2RAD;
        }
        if (GetRandomValue(0, 80) == 1) {
            state = rm::peep_state::IDLE;
            anim_frame = 0;
            anim_num = 0;
            phys.vel.x = 0;
            phys.vel.z = 0;
        }
    } else {
        if (GetRandomValue(0, 80) == 1) {
            state = rm::peep_state::WALK;
            phys.vel.x = 0;
            phys.vel.z = 0;
            phys.acc.z = 0.05f;
            phys.integrate(1.0, &t);
            phys.acc.z = 0.0f;
            anim_num = 1;
            anim_frame = 0;
        }
    }
}
