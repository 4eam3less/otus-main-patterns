#pragma once

class IFuelManager {
public:
    virtual int get_fuel_level() const = 0;
    virtual void set_fuel_level(int level) = 0;
    virtual int fuel_consumption() const  = 0;
    virtual ~IFuelManager() = default;
};