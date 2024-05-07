#pragma once
#include "movable.hpp"
#include "vec2.hpp"

void move(IMovable &movable){
    movable.set_position(movable.get_position() + movable.get_velocity());
}