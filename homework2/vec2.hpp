#pragma once
#include <compare>

struct Vec2{
    int x;
    int y;

    auto operator<=>(const Vec2&) const = default;
    Vec2& operator+=(const Vec2 &other){
        x+= other.x;
        y+= other.y;
        return *this;
    }
};

inline const Vec2 operator+(const Vec2& lhs, const Vec2& rhs){
    Vec2 ret(lhs);
    ret += rhs;
    return ret;
}