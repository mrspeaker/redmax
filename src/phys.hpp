#ifndef PHYS_HPP
#define PHYS_HPP

#include <raylib-cpp.hpp>
#import <trans.hpp>

namespace rm {

struct phys {
    raylib::Vector3 vel;
    raylib::Vector3 acc;

    void integrate(float dt, rm::trans *t);
};

} // namespace rm

#endif // PHYS_HPP
