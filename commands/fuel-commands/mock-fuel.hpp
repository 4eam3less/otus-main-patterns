#pragma once

#include "fuel-manager-interface.hpp"
#include <gmock/gmock.h>

class FuelManagerMock : public IFuelManager {
public:
    MOCK_METHOD(int, get_fuel_level, (), (const, override));
    MOCK_METHOD(void, set_fuel_level, (int), (override));
    MOCK_METHOD(int, fuel_consumption, (), (const, override));
};