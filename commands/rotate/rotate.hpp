#pragma once
#include "rotable.hpp"
#include "angle.hpp"
#include "../command-interface.hpp"
#include <memory>

class RotateCommand : public ICommand {
public:
    explicit RotateCommand(std::shared_ptr<IRotable> rotable) : rotable_(rotable) {}
    void execute() {
        rotable_->set_angle(rotable_->get_angle() + rotable_->get_angular_velocity());
    }
private:
    std::shared_ptr<IRotable> rotable_;
};