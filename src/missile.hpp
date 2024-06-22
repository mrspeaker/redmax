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
    missile();
    missile(raylib::Vector3 *t):target(t){};

    void update(float dt);
};

} // namespace

#endif // MISSILE_HPP
