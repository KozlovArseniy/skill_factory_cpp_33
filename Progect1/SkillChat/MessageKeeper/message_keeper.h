//
// Created by arseniy on 10.08.23.
//
#pragma once

#include <string>
#include <vector>
#include "../Message/message.h"
#include "../User/user.h"
using std::string, std::vector;

class MessageKeeper {
public:
    virtual void AddNewUser(const User& user) = 0;
    virtual void SendMessageToUserByLogin( string current_login, string other_login, const Message &msg ) = 0;
    virtual vector<Message> GetAllMessageByLogin( string current_login, string other_login ) = 0; /// переписка с конкретным человеком
    virtual vector<Message> ReadAllUnreadMessage( string current_login, string other_login ) = 0; /// непрочитанные сообщения от всех людей
    virtual void SetUnreadMessage( const Message &msg ) = 0;
    virtual void SetReadMessage( const Message &msg ) = 0;
};
