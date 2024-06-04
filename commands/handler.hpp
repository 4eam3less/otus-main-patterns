#pragma once

#include "command-interface.hpp"
#include <typeinfo>
#include <memory>
#include <map>
#include <functional>


using func = std::function<std::shared_ptr<ICommand>(std::shared_ptr<ICommand>, const std::exception&)>;

class Handler {
public:
    std::shared_ptr<ICommand> handle(std::shared_ptr<ICommand> cmd, const std::exception &e) const;

    void registre_handle(std::shared_ptr<const ICommand> cmd, const std::exception &e, func handler);

    void registre_handle(const ICommand& cmd, const std::exception &e, func handler);

    void unregistre_handle(std::shared_ptr<const ICommand> cmd, const std::exception &e);

    void unregistre_handle(const ICommand& cmd, const std::exception &e);
    
    size_t size() const;

private:
    std::unordered_map<std::string,func> store_;
};