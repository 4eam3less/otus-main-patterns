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

TEST(Rotate, CorrectRotate) {
    std::shared_ptr<IRotable> rotable_mock(new RotateMock());
    RotateCommand cmd(rotable_mock);
    EXPECT_CALL(dynamic_cast<RotateMock&>(*rotable_mock), get_angle()).WillOnce(Return(Angle{4, 8}));
    EXPECT_CALL(dynamic_cast<RotateMock&>(*rotable_mock), get_angular_velocity()).WillOnce(Return(Angle{1, 4}));
    EXPECT_CALL(dynamic_cast<RotateMock&>(*rotable_mock), set_angle(Angle{3,4})).Times(1);
    EXPECT_NO_THROW(cmd.execute());
}

TEST(Rotate, GetAngleException) {
    std::shared_ptr<IRotable> rotable_mock(new RotateMock());
    RotateCommand cmd(rotable_mock);
    EXPECT_CALL(dynamic_cast<RotateMock&>(*rotable_mock), get_angle()).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(cmd.execute(), std::runtime_error);
}

TEST(Rotate, GetAngularVelocityException) {
    std::shared_ptr<IRotable> rotable_mock(new RotateMock());
    RotateCommand cmd(rotable_mock);
    EXPECT_CALL(dynamic_cast<RotateMock&>(*rotable_mock), get_angular_velocity()).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(cmd.execute(), std::runtime_error);
}

TEST(Rotate, SetAngleException) {
    std::shared_ptr<IRotable> rotable_mock(new RotateMock());
    RotateCommand cmd(rotable_mock);
    EXPECT_CALL(dynamic_cast<RotateMock&>(*rotable_mock), get_angle()).WillOnce(Return(Angle{4, 8}));
    EXPECT_CALL(dynamic_cast<RotateMock&>(*rotable_mock), get_angular_velocity()).WillOnce(Return(Angle{2, 4}));
    EXPECT_CALL(dynamic_cast<RotateMock&>(*rotable_mock), set_angle(Angle{1,1})).WillOnce(Throw(std::runtime_error("")));
    EXPECT_THROW(cmd.execute(), std::runtime_error);
}