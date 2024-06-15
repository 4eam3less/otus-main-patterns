#pragma once

#include "../command-interface.hpp"
#include "fuel-manager-interface.hpp"
#include <memory>

class CheckFuelComamnd : public ICommand {
public:
    explicit CheckFuelComamnd(std::shared_ptr<const IFuelManager> fuel_manager) : fuel_manager_(fuel_manager)  {}
    void execute() override {
        if (0 > (fuel_manager_->get_fuel_level() - fuel_manager_->fuel_consumption()))
            throw std::runtime_error("too little fuel");
    }
private:
    std::shared_ptr<const IFuelManager> fuel_manager_;
};

class BurnFuelCommand : public ICommand {
public:
    explicit BurnFuelCommand(std::shared_ptr<IFuelManager> fuel_manager) : fuel_manager_(fuel_manager)  {}
    void execute() override {
        fuel_manager_->set_fuel_level(fuel_manager_->get_fuel_level() - fuel_manager_->fuel_consumption());
    }
private:
    std::shared_ptr<IFuelManager> fuel_manager_;
};
