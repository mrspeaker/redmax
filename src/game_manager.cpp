#include <game_manager.hpp>
#include <iostream>

rm::game_manager::game_manager() {
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 4; i++) {
            rm::tower t{};
            t.pos.y = 0.1f;
            t.pos.x = (j - 1) * 30.0f;
            t.pos.z = (i - 2) * 45.0f + 25.0f;
            towers.push_back(t);
        }
    }
};

void rm::game_manager::update(float dt) {
    //
}
