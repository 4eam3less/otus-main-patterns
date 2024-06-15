#pragma once

#include "../command-interface.hpp"
#include "uobject.hpp"
#include <numbers>
#include <math.h>

class MovableAdapter : public IMovable {
public:
    MovableAdapter(std::shared_ptr<UObject> obj) : object_(obj) {}
    
    Vec2 get_position() override {
        return object_->operator[]("position").get<Vec2>();
    }

    void set_position(const Vec2 &position) override {
        object_->set_property("position", Property(position));
    }

    Vec2 get_velocity() override {
        const Angle angle = object_->operator[]("angle").get<Angle>();
        const int velocity = object_->operator[]("velocity").get<int>();
        double rad = 2.0 * std::numbers::pi_v<double> * angle.direction / angle.n;
        return Vec2{static_cast<int>(velocity * std::cos(rad)),
                    static_cast<int>(velocity * std::sin(rad))};
    }

private:
    std::shared_ptr<UObject> object_;
};
