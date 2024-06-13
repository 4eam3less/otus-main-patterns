#pragma once

#include "macro-command.hpp"
#include "../fuel-commands/fuel-commands.hpp"
#include "../move/move.hpp"

class MoveMacroCommand : public MacroCommand {
public:
    MoveMacroCommand(std::shared_ptr<IMovable> movable, std::shared_ptr<IFuelManager> fuel_manager) :
    MacroCommand({std::queue<std::shared_ptr<ICommand>>({
            std::make_shared<CheckFuelComamnd>(fuel_manager),
            std::make_shared<MoveCommand>(movable),
            std::make_shared<BurnFuelCommand>(fuel_manager)
        })}) {}
};