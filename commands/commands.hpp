#pragma once

#include "command-interface.hpp"
#include <typeinfo>
#include <memory>
#include <map>
#include <iostream>
#include <queue>

class CommandRepeater : public ICommand{
public:
    CommandRepeater(std::shared_ptr<ICommand> cmd) : cmd_(cmd) {}

    void execute(){
        cmd_->execute();
    }
    ~CommandRepeater(){
    }
private:
    std::shared_ptr<ICommand> cmd_;
};

class CommandTwiceRepeater : public ICommand{
public:
    CommandTwiceRepeater(std::shared_ptr<ICommand> cmd) : cmd_(cmd) {}

    void execute(){
        cmd_->execute();
    }
private:
    std::shared_ptr<ICommand> cmd_;
};

class CommandLogWriter : public ICommand{
public:
    CommandLogWriter(const std::string error) : error_(error) {}

    void execute(){
        std::cout << "LOG: " << error_ << std::endl;
    }
private:
    const std::string error_;
};

class CommandAdder : public ICommand{
public:
    CommandAdder(std::queue<std::shared_ptr<ICommand>>& commands, std::shared_ptr<ICommand> cmd)
     : commands_(commands), cmd_(cmd) {}
    void execute() {
        commands_.push(cmd_);
    }
private:
    std::queue<std::shared_ptr<ICommand>>& commands_;
    std::shared_ptr<ICommand> cmd_;
};

class CommandEmpty : public ICommand{
public:
    void execute() {}
};
