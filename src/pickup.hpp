#ifndef PICKUP_HPP
#define PICKUP_HPP

#import <trans.hpp>
#import <item.hpp>

namespace rm {

struct pickup {
  rm::trans t;
    item_type type=item_type::NONE;
    void update(float dt);
    pickup()=default;
    pickup(item_type type):type(type){};
};

}; // namespace rm

#endif // PICKUP_HPP
