#include "fuel-commands.hpp"
#include "mock-fuel.hpp"
#include <exception>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::Throw;
using testing::Return;

TEST(CheckFuelComamnd, IncorrectVaule) {
    std::shared_ptr<IFuelManager> fuel_manager_mock(new FuelManagerMock());
    CheckFuelComamnd check_fuel_comamnd(fuel_manager_mock);
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), get_fuel_level()).WillOnce(Return(10));
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), fuel_consumption()).WillOnce(Return(35));
    EXPECT_THROW(check_fuel_comamnd.execute(), std::runtime_error);
}

TEST(CheckFuelComamnd, CorrectVaule) {
    std::shared_ptr<IFuelManager> fuel_manager_mock(new FuelManagerMock());
    CheckFuelComamnd check_fuel_comamnd(fuel_manager_mock);
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), get_fuel_level()).WillOnce(Return(100));
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), fuel_consumption()).WillOnce(Return(10));
    EXPECT_NO_THROW(check_fuel_comamnd.execute());
}

TEST(BurnFuelCommand, IncorrectVaule) {
    std::shared_ptr<IFuelManager> fuel_manager_mock(new FuelManagerMock());
    BurnFuelCommand check_fuel_comamnd(fuel_manager_mock);

    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), get_fuel_level()).WillOnce(Return(25));
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), fuel_consumption()).WillOnce(Return(26));
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), set_fuel_level(-1)).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(check_fuel_comamnd.execute(), std::runtime_error);
}

TEST(BurnFuelCommand, CorrectVaule) {
    std::shared_ptr<IFuelManager> fuel_manager_mock(new FuelManagerMock());
    BurnFuelCommand check_fuel_comamnd(fuel_manager_mock);
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), get_fuel_level()).WillOnce(Return(50));
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), fuel_consumption()).WillOnce(Return(25));
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), set_fuel_level(25)).Times(1);
    EXPECT_NO_THROW(check_fuel_comamnd.execute());
}