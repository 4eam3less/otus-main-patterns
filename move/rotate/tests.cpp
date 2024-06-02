#include "rotate.hpp"
#include <exception>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::Throw;
using testing::Return;

class RotateMock : public IRotable {
public:
    MOCK_METHOD(Angle, get_angle, (), (override));
    MOCK_METHOD(void, set_angle, (const struct Angle&), (override));
    MOCK_METHOD(Angle, get_angular_velocity, (), (override));
};

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