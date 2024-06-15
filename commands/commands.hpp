#pragma once

#include "command-interface.hpp"
#include <memory>
#include <iostream>
#include <queue>

class CommandRepeater : public ICommand{
public:
    explicit CommandRepeater(std::shared_ptr<ICommand> cmd) : cmd_(cmd) {}

    void execute() override {
        cmd_->execute();
    }
    ~CommandRepeater(){
    }
private:
    std::shared_ptr<ICommand> cmd_;
};

class CommandTwiceRepeater : public ICommand{
public:
    explicit CommandTwiceRepeater(std::shared_ptr<ICommand> cmd) : cmd_(cmd) {}

    void execute() override {
        cmd_->execute();
    }
private:
    std::shared_ptr<ICommand> cmd_;
};

class CommandLogWriter : public ICommand{
public:
    explicit CommandLogWriter(const std::string error) : error_(error) {}

    void execute() override {
        std::cout << "LOG: " << error_ << std::endl;
    }
private:
    const std::string error_;
};

class CommandAdder : public ICommand{
public:
    explicit CommandAdder(std::queue<std::shared_ptr<ICommand>>& commands, std::shared_ptr<ICommand> cmd)
     : commands_(commands), cmd_(cmd) {}
    void execute() override {
        commands_.push(cmd_);
    }
private:
    std::queue<std::shared_ptr<ICommand>>& commands_;
    std::shared_ptr<ICommand> cmd_;
};

class CommandEmpty : public ICommand{
public:
    void execute() override {}
};
