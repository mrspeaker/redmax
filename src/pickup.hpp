#ifndef PICKUP_HPP
#define PICKUP_HPP

#import <trans.hpp>

namespace rm {

struct pickup {
    rm::trans t;
    void update(float dt);
};

}; // namespace rm

#endif // PICKUP_HPP
