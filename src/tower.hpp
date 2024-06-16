#ifndef TOWER_H
#define TOWER_H

#include <Vector3.hpp>

namespace rm {

class tower {
public:
    raylib::Vector3 pos;
    raylib::Vector3 rot;
    raylib::Vector3 scale;

    tower();
};

} // namespace rm

#endif // TOWER_H
