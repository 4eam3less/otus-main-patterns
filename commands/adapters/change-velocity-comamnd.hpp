#pragma once

#include "../command-interface.hpp"
#include "../move/movable.hpp"
#include "../move/vec2.hpp"
#include <memory>

class ChangeVelocityComamnd : public ICommand {
public:
    ChangeVelocityComamnd(std::shared_ptr<IMovable> movable) : movable_(movable) {}
    
    void execute() {
        movable_->set_position(movable_->get_position() + movable_->get_velocity());
    }
    
private:
    std::shared_ptr<IMovable> movable_;
};