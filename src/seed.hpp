#ifndef SEED_HPP
#define SEED_HPP

#import <trans.hpp>
#import <item.hpp>

namespace rm {

enum class seed_state {
    FALLING,
    LANDED
};

struct seed {
    rm::trans t;
    rm::item_type type;
    rm::seed_state state;
    void update(float dt);
};
    
}; // namespace rm

#endif // SEED_HPP
