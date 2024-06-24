#ifndef PLANE_H
#define PLANE_H

#import <trans.hpp>

namespace rm {

class plane {
public:
    rm::trans t;

    float speed=0;

    plane();
    void update(float dt, bool is_left, bool is_right, bool is_up, bool is_down);
    bool flying();
};

} // namespace rm

#endif // PLANE_H
