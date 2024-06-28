#ifndef MATH_HPP
#define MATH_HPP

#import <raylib-cpp.hpp>

namespace rm {

inline float angle(const Vector2& a, const Vector2& b) {
    return atan2f(b.y - a.y, b.x - a.x);
}

inline Vector2 toVec2(const Vector3& v) {
    return Vector2{v.x, v.z};
}

}; // namespace rm

#endif // MATH_HPP
