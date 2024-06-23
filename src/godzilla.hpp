#ifndef GODZILLA_HPP
#define GODZILLA_HPP

#import <trans.hpp>

namespace rm {

class godzilla {
public:
    rm::trans t;
    float cooldown;
    void update(float dt);
    bool can_fire();
};

} // namespace

#endif // GODZILLA_HPP
