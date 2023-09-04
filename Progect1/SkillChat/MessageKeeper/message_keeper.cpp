//
// Created by arseniy on 23.08.23.
//
#include "message_keeper.h"
#include "../Exception/chat_exception.h"

void MessageKeeper::AddNewUser(const User& user){
    (void) user;
    throw NotImplementedException("MessageKeeper::AddNewUser");
};

User MessageKeeper::LoginUser(const string& login, const string& password) {
    (void) login;
    (void) password;
    throw NotImplementedException("MessageKeeper::LoginUser");
};

void MessageKeeper::SendMessageToUserByLogin( const string &current_login, const string &other_login, const Message &msg ){
    (void) current_login;
    (void) other_login;
    (void) msg;
    throw NotImplementedException("MessageKeeper::SendMessageToUserByLogin");
}

vector<Message> MessageKeeper::GetAllMessageByLogin( const string &current_login, const string &other_login ){
    (void) current_login;
    (void) other_login;
    throw NotImplementedException("MessageKeeper::GetAllMessageByLogin");
}

vector<Message> MessageKeeper::ReadAllUnreadMessage( const string &current_login ){
    (void) current_login;
    throw NotImplementedException("MessageKeeper::ReadAllUnreadMessage");
}

void MessageKeeper::SetUnreadMessage( const Message &msg ){
    (void) msg;
    throw NotImplementedException("MessageKeeper::SetUnreadMessage");
}

void MessageKeeper::SetReadMessage( const Message &msg ){
    (void) msg;
    throw NotImplementedException("MessageKeeper::SetReadMessage");
}

MessageKeeper::~MessageKeeper() {
}

