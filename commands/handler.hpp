#pragma once

#include "command-interface.hpp"
#include "commands.hpp"
#include <typeinfo>
#include <memory>
#include <map>

using func = std::function<std::shared_ptr<ICommand>(std::shared_ptr<ICommand>, const std::exception&)>;

std::string make_name(const char* cmd, const char* e){
    return std::string(cmd) + "_" + std::string(e);
}

class Handler {
public:
    std::shared_ptr<ICommand> handle(std::shared_ptr<ICommand> cmd, const std::exception &e){
        ICommand& type = *(cmd.get());
        std::string name = make_name(typeid(type).name(), typeid(e).name());

        auto it = store_.find(name);
        if (it != store_.end()) {
            return it->second(cmd, e);
        }
        return std::make_shared<CommandEmpty>();
    }

    void registre_handle(std::shared_ptr<const ICommand> cmd, const std::exception &e, func handler){
        registre_handle(*(cmd.get()), e, handler);
    }

    void registre_handle(const ICommand& cmd, const std::exception &e, func handler){
        store_[make_name(typeid(cmd).name(), typeid(e).name())] = handler;
    }
    void unregistre_handle(std::shared_ptr<const ICommand> cmd, const std::exception &e){
        unregistre_handle(*(cmd.get()), e);
    }

    void unregistre_handle(const ICommand& cmd, const std::exception &e) {
        std::string name = make_name(typeid(cmd).name(), typeid(e).name());
        auto it = store_.find(name);
        if (it != store_.end()) {
            store_.erase(it);
        }
    }
    
    size_t size() const {
        return store_.size();
    }
    
private:
    std::unordered_map<std::string,func> store_;
};