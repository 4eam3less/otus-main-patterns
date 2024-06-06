#include "move.hpp"
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

TEST(Move, CorrectMove) {
    std::shared_ptr<IMovable> movable_mock(new MoveMock());
    MoveCommand cmd(movable_mock);
    EXPECT_CALL(dynamic_cast<MoveMock&>(*movable_mock), get_position()).WillOnce(Return(Vec2{12, 5}));
    EXPECT_CALL(dynamic_cast<MoveMock&>(*movable_mock), get_velocity()).WillOnce(Return(Vec2{-7, 3}));
    EXPECT_CALL(dynamic_cast<MoveMock&>(*movable_mock), set_position(Vec2{5,8})).Times(1);
    EXPECT_NO_THROW(cmd.execute());
}

TEST(Move, GetPositionException) {
    std::shared_ptr<IMovable> movable_mock(new MoveMock());
    MoveCommand cmd(movable_mock);
    EXPECT_CALL(dynamic_cast<MoveMock&>(*movable_mock), get_position()).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(cmd.execute(), std::runtime_error);
}

TEST(Move, GetVelocityException) {
    std::shared_ptr<IMovable> movable_mock(new MoveMock());
    MoveCommand cmd(movable_mock);
    EXPECT_CALL(dynamic_cast<MoveMock&>(*movable_mock), get_velocity()).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(cmd.execute(), std::runtime_error);
}

TEST(Move, SetPositionException) {
    std::shared_ptr<IMovable> movable_mock(new MoveMock());
    MoveCommand cmd(movable_mock);
    EXPECT_CALL(dynamic_cast<MoveMock&>(*movable_mock), get_position()).WillOnce(Return(Vec2{5, 5}));
    EXPECT_CALL(dynamic_cast<MoveMock&>(*movable_mock), get_velocity()).WillOnce(Return(Vec2{1, 2}));
    EXPECT_CALL(dynamic_cast<MoveMock&>(*movable_mock), set_position(Vec2{6,7})).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(cmd.execute(), std::runtime_error);
}