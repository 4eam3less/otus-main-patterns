#include "handler.hpp"
#include "command-interface.hpp"
#include "commands.hpp"
#include <typeinfo>
#include <memory>
#include <map>
#include <functional>

using func = std::function<std::shared_ptr<ICommand>(std::shared_ptr<ICommand>, const std::exception&)>;

std::string make_name(const char* cmd, const char* e){
    return std::string(cmd) + "_" + std::string(e);
}
std::shared_ptr<ICommand> Handler::handle(std::shared_ptr<ICommand> cmd, const std::exception &e) const{
    ICommand& type = *(cmd.get());
    std::string name = make_name(typeid(type).name(), typeid(e).name());
    auto it = store_.find(name);
    if (it != store_.end()) {
        return it->second(cmd, e);
    }
    return std::make_shared<CommandEmpty>();
}

void Handler::registre_handle(std::shared_ptr<const ICommand> cmd, const std::exception &e, func handler){
    registre_handle(*(cmd.get()), e, handler);
}

void Handler::registre_handle(const ICommand& cmd, const std::exception &e, func handler){
    store_[make_name(typeid(cmd).name(), typeid(e).name())] = handler;
}

void Handler::unregistre_handle(std::shared_ptr<const ICommand> cmd, const std::exception &e){
    unregistre_handle(*(cmd.get()), e);
}

void Handler::unregistre_handle(const ICommand& cmd, const std::exception &e) {
    std::string name = make_name(typeid(cmd).name(), typeid(e).name());
    auto it = store_.find(name);
    if (it != store_.end()) {
        store_.erase(it);
    }
}
    
size_t Handler::size() const {
    return store_.size();
}