#import <peep.hpp>

#import <math.hpp>

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

/*
void update2(float dt, const Vector2& target) {
  phys.integrate(dt, &t);

  auto v = toVec2(t.pos);
  auto a = rm::angle(v, target);

  auto rot_speed = 2.0f;
  if (a > t.rot.y) t.rot.y += rot_speed * dt;
  if (a < t.rot.y) t.rot.y -= rot_speed * dt;


  if (GetRandomValue(0, 50) == 1) {
      t.rot.y = t.rot.y + GetRandomValue(0, 45) * DEG2RAD;
  }
}
*/
