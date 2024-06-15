#include "macro-move.hpp"
#include "../fuel-commands/mock-fuel.hpp"
#include <exception>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::Throw;
using testing::Return;

class MoveMock : public IMovable {
public:
    MOCK_METHOD(Vec2, get_position, (), (override));
    MOCK_METHOD(void, set_position, (const struct Vec2&), (override));
    MOCK_METHOD(Vec2, get_velocity, (), (override));
};

TEST(MoveMacroCommand, CorrectMacroMove) {
    std::shared_ptr<IMovable> movable_mock(new MoveMock());
    std::shared_ptr<IFuelManager> fuel_manager_mock(new FuelManagerMock());
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), get_fuel_level()).WillRepeatedly(Return(100));
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), fuel_consumption()).WillRepeatedly(Return(100));
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), set_fuel_level(0)).Times(1);
    EXPECT_CALL(dynamic_cast<MoveMock&>(*movable_mock), get_position()).WillOnce(Return(Vec2{1, 1}));
    EXPECT_CALL(dynamic_cast<MoveMock&>(*movable_mock), get_velocity()).WillOnce(Return(Vec2{124, 91}));
    EXPECT_CALL(dynamic_cast<MoveMock&>(*movable_mock), set_position(Vec2{125,92})).Times(1);
    MoveMacroCommand cmd(movable_mock, fuel_manager_mock);
    cmd.execute();
}

TEST(MoveMacroCommand, IncorrectMacroMove) {
    std::shared_ptr<IMovable> movable_mock(new MoveMock());
    std::shared_ptr<IFuelManager> fuel_manager_mock(new FuelManagerMock());
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), get_fuel_level()).WillRepeatedly(Return(10));
    EXPECT_CALL(dynamic_cast<FuelManagerMock&>(*fuel_manager_mock), fuel_consumption()).WillRepeatedly(Return(30));
    MoveMacroCommand cmd(movable_mock, fuel_manager_mock);
    EXPECT_THROW(cmd.execute(), CommandException);
}