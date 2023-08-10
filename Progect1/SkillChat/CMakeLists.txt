cmake_minimum_required(VERSION 3.25)
project(SkillChar)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(MessageKeeper/SqlLite/SQLiteCpp)

set(SOURCE
        MessageKeeper/SqlLite/sql_lite_message_keeper.cpp
        MessageKeeper/SqlLite/SqLiteException/sql_lite_exception.cpp
        MessageKeeper/MessageKeeperException/message_keeper_exception.cpp
        Message/message.cpp
        Message/message_exceptions.cpp
        Exception/chat_exception.cpp
        )
set(HEADERS
        MessageKeeper/message_keeper.h
        MessageKeeper/SqlLite/SqLiteException/sql_lite_exception.h
        MessageKeeper/MessageKeeperException/message_keeper_exception.h
        MessageKeeper/SqlLite/sql_lite_message_keeper.h
        Message/message.h
        Message/message_exceptions.h
        Exception/chat_exception.h
        )
add_executable(SkillChar main.cpp ${SOURCE} ${HEADERS})

target_link_libraries(SkillChar
        SQLiteCpp
        sqlite3
        pthread
        dl
        )