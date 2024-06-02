#include "handler.hpp"

#include <exception>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(Handler, Registre) {
    Handler handler;
    EXPECT_EQ(handler.size(), 0);

    handler.registre_handle(std::make_shared<CommandEmpty>(), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>cmd, const std::exception &){
        return std::make_shared<CommandRepeater>(cmd);
    });
    EXPECT_EQ(handler.size(), 1);

    handler.registre_handle(std::make_shared<CommandRepeater>(std::make_shared<CommandEmpty>()), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>cmd, const std::exception &){
        return std::make_shared<CommandTwiceRepeater>(cmd);
    });
    EXPECT_EQ(handler.size(), 2);
}

TEST(Handler, Unregistre) {
    Handler handler;
    handler.registre_handle(std::make_shared<CommandEmpty>(), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>cmd, const std::exception &){
        return std::make_shared<CommandRepeater>(cmd);
    });
    handler.registre_handle(std::make_shared<CommandRepeater>(std::make_shared<CommandEmpty>()), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>cmd, const std::exception &){
        return std::make_shared<CommandTwiceRepeater>(cmd);
    });
    handler.registre_handle(std::make_shared<CommandTwiceRepeater>(std::make_shared<CommandEmpty>()), std::runtime_error("2 error!"),
                            [](std::shared_ptr<ICommand>, const std::exception &e){
        return std::make_shared<CommandLogWriter>(e.what());
    });
    
    EXPECT_EQ(handler.size(), 3);

    handler.unregistre_handle(std::make_shared<CommandEmpty>(), std::runtime_error(""));
    EXPECT_EQ(handler.size(), 2);

    handler.unregistre_handle(std::make_shared<CommandRepeater>(std::make_shared<CommandEmpty>()), std::runtime_error(""));
    EXPECT_EQ(handler.size(), 1);

    handler.unregistre_handle(std::make_shared<CommandTwiceRepeater>(std::make_shared<CommandEmpty>()), std::runtime_error(""));
    EXPECT_EQ(handler.size(), 0);
}

TEST(Handler, GetCommand) {
    Handler handler;
    handler.registre_handle(std::make_shared<CommandEmpty>(), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>cmd, const std::exception &){
        return std::make_shared<CommandRepeater>(cmd);
    });
    handler.registre_handle(std::make_shared<CommandRepeater>(std::make_shared<CommandEmpty>()), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>cmd, const std::exception &){
        return std::make_shared<CommandTwiceRepeater>(cmd);
    });
    
    auto res_empty = handler.handle(std::make_shared<CommandEmpty>(), std::runtime_error(""));
    ICommand& cmd_empty = *(res_empty.get());
    ASSERT_STREQ(typeid(cmd_empty).name(), typeid(CommandRepeater).name());

    auto res_repeator = handler.handle(std::make_shared<CommandRepeater>(std::make_shared<CommandEmpty>()), std::runtime_error(""));
    ICommand& cmd_repeator = *(res_repeator.get());
    ASSERT_STREQ(typeid(cmd_repeator).name(), typeid(CommandTwiceRepeater).name());
}

TEST(Handler, GetUnknowCommand) {
    Handler handler;
    handler.registre_handle(std::make_shared<CommandRepeater>(std::make_shared<CommandEmpty>()), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>cmd, const std::exception &){
        return std::make_shared<CommandRepeater>(cmd);
    });
    auto res = handler.handle(std::make_shared<CommandLogWriter>("error"), std::logic_error(""));
    ICommand& cmd = *(res.get());
    ASSERT_STREQ(typeid(cmd).name(), typeid(CommandEmpty).name());
}
