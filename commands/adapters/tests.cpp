#include "change-velocity-comamnd.hpp"
#include "movable-adapter.hpp"
#include "uobject.hpp"
#include <exception>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(ChangeVelocityComamnd, PositiveVelocity) {
    std::shared_ptr<UObject> object = std::make_shared<UObject>();
    object->set_property("position", Property(Vec2{1, 1}));
    object->set_property("angle", Property(Angle{4, 8}));
    object->set_property("velocity", 5);
    std::shared_ptr<MovableAdapter> adapter = std::make_shared<MovableAdapter>(object);
    ChangeVelocityComamnd cmd(adapter);
    EXPECT_NO_THROW(cmd.execute());
    Vec2 result{-4,1};
    EXPECT_EQ(adapter->get_position(), result);
}

TEST(ChangeVelocityComamnd, ZeroVelocity) {
    std::shared_ptr<UObject> object = std::make_shared<UObject>();
    object->set_property("position", Property(Vec2{1, 1}));
    object->set_property("angle", Property(Angle{7, 8}));
    object->set_property("velocity", 0);
    std::shared_ptr<MovableAdapter> adapter = std::make_shared<MovableAdapter>(object);
    ChangeVelocityComamnd cmd(adapter);
    EXPECT_NO_THROW(cmd.execute());
    Vec2 result{1,1};
    EXPECT_EQ(adapter->get_position(), result);
}