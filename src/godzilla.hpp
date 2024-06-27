#ifndef GODZILLA_HPP
#define GODZILLA_HPP

#import <trans.hpp>

namespace rm {

enum class godz_state {
    WALK,
    ROAR
};

class godzilla {
public:
    void update(float dt);
    bool can_fire();
    void fire();

    rm::trans t;
    float cooldown=10.0;
    godz_state state=godz_state::WALK;
    float state_time=0.0;
    int anim_num=0;
    int anim_frame=0;
};

} // namespace

#endif // GODZILLA_HPP
