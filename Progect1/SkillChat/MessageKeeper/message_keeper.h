//
// Created by arseniy on 10.08.23.
//
#pragma once

#include <string>
#include <vector>
#include "../Message/message.h"
using std::string, std::vector;

class MessageKeeper {
public:
    virtual void SendMessageToUserByLogin( string current_login, string other_login, Message msg) = 0;
    virtual vector<Message> GetAllMessageByLogin( string current_login, string other_login ) = 0;
    virtual vector<Message> ReadAllUnreadMessage( string current_login ) = 0;
    virtual void SetUnreadMessage( Message msg ) = 0;
    virtual void SetReadMessage( Message msg ) = 0;
};
