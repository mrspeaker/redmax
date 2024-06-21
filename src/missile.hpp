#ifndef MISSILE_HPP
#define MISSILE_HPP

#import <trans.hpp>

namespace rm {

class missile {
public:
    rm::trans t;
    void update();
};

} // namespace

#endif // MISSILE_HPP
