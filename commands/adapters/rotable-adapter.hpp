#pragma once

#include "command-interface.hpp"
#include "command-exeption.hpp"
#include "fuel-manager-interface.hpp"
#include "move/move.hpp"
#include "rotate/rotate.hpp"
#include "uobject.hpp"

#include <typeinfo>
#include <memory>
#include <map>
#include <iostream>
#include <queue>
#include <math.h>
#include <numbers>

class RotableAdapter : public IRotable {
public:
    RotableAdapter(std::shared_ptr<UObject> obj) : object_(obj) {}

    Angle get_angle() override {
        return object_->operator[]("angle").get<Angle>();
    }

    void set_angle(const Angle &angle) override {
        object_->set_property("angle", Property(angle));
    }

    Angle get_angular_velocity() override {
        return object_->operator[]("angular_velocity").get<Angle>();
    }

private:
    std::shared_ptr<UObject> object_;
};
