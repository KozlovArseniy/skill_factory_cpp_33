//
// Created by arseniy on 10.08.23.
//
#pragma once

#include "../message_keeper.h"
#include "sqlite3.h"

class SqlLiteMessageKeeper: public MessageKeeper{
    void SendMessageToUserByLogin( string current_login, string other_login, Message msg) override;
    vector<Message> GetAllMessageByLogin( string current_login, string other_login ) override;
    vector<Message> ReadAllUnreadMessage( string current_login ) override;
    void SetUnreadMessage( Message msg ) override;
    void SetReadMessage( Message msg ) override;
private:
    sqlite3* _data_base_connection;
};
