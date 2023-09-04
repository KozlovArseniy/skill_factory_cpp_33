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
    virtual void AddNewUser(const User& user);
    virtual User LoginUser(const string& login, const string& password);
    virtual void SendMessageToUserByLogin( const string &current_login, const string &other_login, const Message &msg );
    virtual vector<Message> GetAllMessageByLogin( const string &current_login, const string &other_login ); /// переписка с конкретным человеком
    virtual vector<Message> ReadAllUnreadMessage( const string &current_login ); /// непрочитанные сообщения от всех людей
    virtual void SetUnreadMessage( const Message &msg );
    virtual void SetReadMessage( const Message &msg );
    virtual ~MessageKeeper();
};
