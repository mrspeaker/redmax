#ifndef MISSILE_HPP
#define MISSILE_HPP

#import <trans.hpp>
#import <phys.hpp>

namespace rm {

class missile {
public:
    rm::trans t;
    rm::phys phys;
    raylib::Vector3 *target;
    missile()=default;
    missile(raylib::Vector3 *t):target(t){};
    float life;

    bool update(float dt);
};

} // namespace

#endif // MISSILE_HPP
