#ifndef PEEP_HPP
#define PEEP_HPP

#import <trans.hpp>
#import <phys.hpp>

namespace rm {

enum class peep_state {
    IDLE,
    WALK
};

class peep {
public:
    peep();
    void update(float dt);

    rm::trans t;
    rm::phys phys;

    peep_state state=peep_state::IDLE;
    float state_time=0.0;
    int anim_num=0;
    int anim_frame=0;
};

}; // namespace rm

#endif // PEEP_HPP
