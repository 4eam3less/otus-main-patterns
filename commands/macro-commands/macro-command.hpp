#pragma once

#include "../command-interface.hpp"
#include "command-exeption.hpp"
#include <queue>

class MacroCommand : public ICommand {
public:
    explicit MacroCommand(std::queue<std::shared_ptr<ICommand>> commands) : commands_(commands) {}
    void execute() override {
        try {
            while (!commands_.empty()) {
                auto cmd = commands_.front();
                cmd->execute();
                commands_.pop();
            }    
        }
        catch(const std::exception& e) {
            throw CommandException(e.what());
        }
    }
private:
    std::queue<std::shared_ptr<ICommand>> commands_;
};
