#include "move.hpp"
#include "rotate.hpp"
#include <exception>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::Throw;
using testing::Return;

class MoveMock : public IMovable {
public:
    MOCK_METHOD(Vec2, get_position, (), (override));
    MOCK_METHOD(void, set_position, (struct Vec2), (override));
    MOCK_METHOD(Vec2, get_velocity, (), (override));
};

class RotateMock : public IRotable {
public:
    MOCK_METHOD(Angle, get_angle, (), (override));
    MOCK_METHOD(void, set_angle, (struct Angle), (override));
    MOCK_METHOD(Angle, get_angular_velocity, (), (override));
};

TEST(Move, CorrectMove) {
    MoveMock movable_mock;
    EXPECT_CALL(movable_mock, get_position()).WillOnce(Return(Vec2{12, 5}));
    EXPECT_CALL(movable_mock, get_velocity()).WillOnce(Return(Vec2{-7, 3}));
    EXPECT_CALL(movable_mock, set_position(Vec2{5,8})).Times(1);
    move(movable_mock);
}

TEST(Move, GetPositionException) {
    MoveMock movable_mock;
    EXPECT_CALL(movable_mock, get_position()).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(move(movable_mock), std::runtime_error);
}

TEST(Move, GetVelocityException) {
    MoveMock movable_mock;
    EXPECT_CALL(movable_mock, get_velocity()).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(move(movable_mock), std::runtime_error);
}

TEST(Move, SetPositionException) {
    MoveMock movable_mock;
    EXPECT_CALL(movable_mock, get_position()).WillOnce(Return(Vec2{5, 5}));
    EXPECT_CALL(movable_mock, get_velocity()).WillOnce(Return(Vec2{1, 2}));
    EXPECT_CALL(movable_mock, set_position(Vec2{6,7})).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(move(movable_mock), std::runtime_error);
}

TEST(rotate, CorrectRotate) {
    RotateMock rotable_mock;
    EXPECT_CALL(rotable_mock, get_angle()).WillOnce(Return(Angle{4, 8}));
    EXPECT_CALL(rotable_mock, get_angular_velocity()).WillOnce(Return(Angle{1, 4}));
    EXPECT_CALL(rotable_mock, set_angle(Angle{3,4})).Times(1);
    rotate(rotable_mock);
}

TEST(rotate, GetAngleException) {
    RotateMock rotable_mock;
    EXPECT_CALL(rotable_mock, get_angle()).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(rotate(rotable_mock), std::runtime_error);
}

TEST(rotate, GetAngularVelocityException) {
    RotateMock rotable_mock;
    EXPECT_CALL(rotable_mock, get_angular_velocity()).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(rotate(rotable_mock), std::runtime_error);
}

TEST(rotate, SetAngleException) {
    RotateMock rotable_mock;
    EXPECT_CALL(rotable_mock, get_angle()).WillOnce(Return(Angle{4, 8}));
    EXPECT_CALL(rotable_mock, get_angular_velocity()).WillOnce(Return(Angle{2, 4}));
    EXPECT_CALL(rotable_mock, set_angle(Angle{1,1})).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(rotate(rotable_mock), std::runtime_error);
}