cmake_minimum_required(VERSION 3.25)
project(SkillChat)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(MessageKeeper/SqlLite/SQLiteCpp)

add_compile_definitions(SQL_LITE) # Задаем вид хранилища сообщений

add_compile_definitions(CONSOLE_UI) # Задаем вид пользовательского интерфейса

set(SOURCE
        MessageKeeper/message_keeper.cpp
        MessageKeeper/SqlLite/sql_lite_message_keeper.cpp
        Message/message.cpp
        Exception/chat_exception.cpp
        User/user.cpp
        Ui/ui.cpp
        Ui/ConsoleUi/console_ui.cpp)
set(HEADERS
        MessageKeeper/message_keeper.h
        MessageKeeper/MessageKeeperException/message_keeper_exception.h
        MessageKeeper/SqlLite/sql_lite_message_keeper.h
        Message/message.h
        Exception/chat_exception.h
        User/user.h
        Ui/ui.h
        Ui/ConsoleUi/console_ui.h)
add_executable(SkillChat main.cpp ${SOURCE} ${HEADERS})

target_link_libraries(SkillChat
        SQLiteCpp
        sqlite3
        pthread
        dl
        )