#pragma once

struct Vec2;

class IMovable{
public:
    virtual Vec2 get_position() = 0;
    virtual void set_position(Vec2 pos) = 0;
    virtual Vec2 get_velocity() = 0;
};