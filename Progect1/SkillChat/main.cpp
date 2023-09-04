#include <iostream>
#include <memory>
#include "MessageKeeper/SqlLite/sql_lite_message_keeper.h"

#include "Ui/ui.h"

#ifdef CONSOLE_UI
    #include "Ui/ConsoleUi/console_ui.h"
#endif


int main() {
    std::unique_ptr<Ui> ui;
#ifdef CONSOLE_UI
    ui = std::make_unique<ConsoleUi>();
#endif
    ui->MainLoop();
    return 0;
}
