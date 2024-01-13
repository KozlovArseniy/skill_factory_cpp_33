#include <iostream>
#include <memory>
#include "MessageKeeper/SqlLite/sql_lite_message_keeper.h"
#include "Logger/logger.h"
#include "Ui/ui.h"

#ifdef CONSOLE_UI
    #include "Ui/ConsoleUi/console_ui.h"
#endif


int main() {
    Logger::Instance().WriteLog( "Старт приложения", InfoMsg );
    std::unique_ptr<Ui> ui;
#ifdef CONSOLE_UI
    ui = std::make_unique<ConsoleUi>();
#endif
    ui->MainLoop();
    Logger::Instance().WriteLog( "Остановка приложения", InfoMsg );
    return 0;
}
