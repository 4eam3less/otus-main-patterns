#pragma once
#include "movable.hpp"
#include "../command-interface.hpp"
#include "vec2.hpp"
#include <memory>

class MoveCommand : public ICommand {
public:
    explicit MoveCommand(std::shared_ptr<IMovable> movable) : movable_(movable) {}
    void execute() {
        movable_->set_position(movable_->get_position() + movable_->get_velocity());
    }
private:
    std::shared_ptr<IMovable> movable_;
};