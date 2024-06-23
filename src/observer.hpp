#ifndef OBSERVER_HPP
#define OBSERVER_HPP
#include <vector>

namespace rm {

enum class game_event {
    SPAWN,
};


class observer {
public:
    virtual ~observer() {}
    virtual void on_notify(game_event event, float x, float y, float z) = 0;
};

class subject {
public:
    void add_observer(observer* ob) {
        observers[num_observers++] = ob;
    }
    void notify(game_event event, float x, float y, float z) {
        for (int i = 0; i < num_observers; i++) {
            observers[i]->on_notify(event, x, y, z);
        }
    }
private:
    observer* observers[5];
    int num_observers;
};

}; // namespace rm

#endif // OBSERVER_HPP
