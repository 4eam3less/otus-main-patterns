#pragma once

struct Angle;

class IRotable{
public:
    virtual Angle get_angle() = 0;
    virtual void set_angle(Angle) = 0;
    virtual Angle get_angular_velocity() = 0;
};
