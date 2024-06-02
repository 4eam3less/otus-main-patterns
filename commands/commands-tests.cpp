#include "command-interface.hpp"
#include "handler.hpp"
#include "commands.hpp"

#include <exception>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <queue>

using testing::Throw;
using testing::Return;

using func = std::function<std::shared_ptr<ICommand>(std::shared_ptr<ICommand>, const std::exception&)>;

class CommandMock : public ICommand {
public:
    MOCK_METHOD(void, execute, (), (override));
};


//6.Реализовать Команду, которая повторяет Команду, выбросившую исключение.
TEST(Commands, Repeat) {
    Handler handler;
    handler.registre_handle(std::make_shared<CommandMock>(), std::runtime_error(""), 
                            [](std::shared_ptr<ICommand> cmd, std::exception){
        return std::make_shared<CommandRepeater>(cmd);
    });
    std::shared_ptr<ICommand> cmd_mock(new CommandMock());
    EXPECT_CALL(dynamic_cast<CommandMock&>(*cmd_mock), execute()).WillRepeatedly(Throw(std::runtime_error("")));
    try {
        cmd_mock->execute();
    } catch (std::exception& e) {
        EXPECT_THROW(handler.handle(cmd_mock, e)->execute(), std::runtime_error);
    }
}
//  // 4.Реализовать Команду, которая записывает информацию о выброшенном исключении в лог.
TEST(Commands, LogWriter) {
    Handler handler;
    handler.registre_handle(std::make_shared<CommandMock>(), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>, const std::exception &e){
        return std::make_shared<CommandLogWriter>(e.what());
    });
    std::shared_ptr<ICommand> cmd_mock (new CommandMock());
    EXPECT_CALL(dynamic_cast<CommandMock&>(*cmd_mock), execute()).WillOnce(Throw(std::runtime_error("mock exception")));
    try {
        cmd_mock->execute();
    } catch (std::exception& e) {
        handler.handle(cmd_mock, e)->execute();
    }
}
// //5.Реализовать обработчик исключения, который ставит Команду, пишущую в лог в очередь Команд.
TEST(Commands, AddToQueueCommand) {
    std::shared_ptr<ICommand> cmd_mock (new CommandMock());
    EXPECT_CALL(dynamic_cast<CommandMock&>(*cmd_mock), execute()).WillRepeatedly(Throw(std::runtime_error("")));
    std::queue<std::shared_ptr<ICommand>> commands;
    commands.push(cmd_mock);

    Handler handler;
    handler.registre_handle(std::make_shared<CommandMock>(), std::runtime_error(""),
                            [&commands](std::shared_ptr<ICommand>cmd, const std::exception &){
        return std::make_shared<CommandAdder>(commands, cmd);
    });
    EXPECT_EQ(commands.size(), 1);
    const auto cmd = commands.front();
    try {
        cmd->execute();
    } catch (std::exception& e) {
        handler.handle(cmd, e)->execute();
    }
    EXPECT_EQ(commands.size(), 2);
}
// //7.Реализовать обработчик исключения, который ставит в очередь Команду - повторитель команды, выбросившей исключение.
TEST(Commands, AddToQueueRepeate) {
    std::shared_ptr<ICommand> cmd_mock (new CommandMock());
    EXPECT_CALL(dynamic_cast<CommandMock&>(*cmd_mock), execute()).WillRepeatedly(Throw(std::runtime_error("")));
    std::queue<std::shared_ptr<ICommand>> commands;
    commands.push(cmd_mock);

    Handler handler;
    handler.registre_handle(std::make_shared<CommandMock>(), std::runtime_error(""),
                            [&commands](std::shared_ptr<ICommand>cmd, const std::exception &){
        return std::make_shared<CommandAdder>(commands, std::make_shared<CommandRepeater>(cmd));
    });
    
    EXPECT_EQ(commands.size(), 1);
    const auto cmd = commands.front();
    try {
        cmd->execute();
    } catch (std::exception& e) {
        handler.handle(cmd, e)->execute();
    }
    EXPECT_EQ(commands.size(), 2);
}
// //8.С помощью Команд из пункта 4 и пункта 6 реализовать следующую обработку исключений:
//при первом выбросе исключения повторить команду, при повторном выбросе исключения записать информацию в лог.
TEST(Commands, RepeateAndLogWrite) {
    std::shared_ptr<ICommand> cmd_mock (new CommandMock());
    EXPECT_CALL(dynamic_cast<CommandMock&>(*cmd_mock), execute()).WillRepeatedly(Throw(std::runtime_error("error")));

    Handler handler;
    handler.registre_handle(std::make_shared<CommandMock>(), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>cmd, const std::exception &){
        return std::make_shared<CommandRepeater>(cmd);
    });
    handler.registre_handle(std::make_shared<CommandRepeater>(std::make_shared<CommandLogWriter>("")), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>, const std::exception &e){
        return std::make_shared<CommandLogWriter>(e.what());
    });

    try{
        cmd_mock->execute();
    } catch (std::exception& e) {
        auto cmd = handler.handle(cmd_mock, e);
        try {
            cmd->execute();
        } catch (std::exception& e) {
            handler.handle(cmd, e)->execute();
        }
    }
}
// //9.Реализовать стратегию обработки исключения - повторить два раза, потом записать в лог. 
// //Указание: создать новую команду, точно такую же как в пункте 6. Тип этой команды будет показывать,
// //что Команду не удалось выполнить два раза.

TEST(Commands, TwiceRepeateAndLogWrite) {
    std::shared_ptr<ICommand> cmd_mock (new CommandMock());
    EXPECT_CALL(dynamic_cast<CommandMock&>(*cmd_mock), execute()).WillRepeatedly(Throw(std::runtime_error("error")));

    Handler handler;
    handler.registre_handle(std::make_shared<CommandMock>(), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>cmd, const std::exception &){
        return std::make_shared<CommandRepeater>(cmd);
    });
    handler.registre_handle(std::make_shared<CommandRepeater>(std::make_shared<CommandLogWriter>("")), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>cmd, const std::exception &){
        return std::make_shared<CommandTwiceRepeater>(cmd);
    });
    handler.registre_handle(std::make_shared<CommandTwiceRepeater>(std::make_shared<CommandLogWriter>("")), std::runtime_error(""),
                            [](std::shared_ptr<ICommand>, const std::exception &e){
        return std::make_shared<CommandLogWriter>(e.what());
    });
    try{
        cmd_mock->execute();
    } catch (std::exception& e) {
        auto cmd = handler.handle(cmd_mock, e);
        try{
            cmd->execute();
        } catch (std::exception& e) {
            auto next_cmd = handler.handle(cmd, e);
            try{
                next_cmd->execute();
            } catch (std::exception& e) {
                handler.handle(next_cmd, e)->execute();
            }
        }
    }
}