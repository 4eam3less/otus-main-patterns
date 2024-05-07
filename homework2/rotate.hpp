#pragma once
#include "rotable.hpp"
#include "angle.hpp"

inline void rotate(IRotable &rotable){
    rotable.set_angle(rotable.get_angle() + rotable.get_angular_velocity());
}