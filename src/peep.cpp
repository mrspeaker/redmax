#import <peep.hpp>

rm::peep::peep() {
    phys.acc.z = 0.05f;
    phys.integrate(1.0, &t);
    phys.acc.z = 0.0f;
}

void rm::peep::update(float dt) {
  phys.integrate(dt, &t);

  if (GetRandomValue(0, 50) == 1) {
      t.rot.y = t.rot.y + GetRandomValue(0, 45) * DEG2RAD;
  }
}
