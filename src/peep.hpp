#ifndef PEEP_HPP
#define PEEP_HPP

#import <trans.hpp>
#import <phys.hpp>

namespace rm {

class peep {
public:
    rm::trans t;
    rm::phys phys;

    peep();
    void update(float dt);
};

}; // namespace rm

#endif // PEEP_HPP
