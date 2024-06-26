#ifndef PEEP_HPP
#define PEEP_HPP

#import <trans.hpp>

namespace rm {

class peep {
public:
    rm::trans t;
    void update(float dt);
};

}; // namespace rm

#endif // PEEP_HPP
