//
// Created by arseniy on 10.08.23.
//
#pragma once

#include "../../Exception/chat_exception.h"

class MessageKeeperException :public ChatException{
public:
    MessageKeeperException(const string& error_text): ChatException(string("from MessageKeeper ") + error_text){}
};

class CannotOpenMessageKeeperException:public MessageKeeperException{
public:
    CannotOpenMessageKeeperException(const string& error_text): MessageKeeperException(string("database not opened " + error_text)){}
};

class CannotCreateStructureException:public MessageKeeperException{
public:
    CannotCreateStructureException(const string& error_text): MessageKeeperException(string("cannot create db structure " + error_text)){}
};

class CannotCreateNewUserException:public MessageKeeperException{
public:
    CannotCreateNewUserException(const string& error_text): MessageKeeperException(string("cannot create new user " + error_text)){}
};

class UserNotFoundException:public MessageKeeperException{
public:
    UserNotFoundException(const string& error_text): MessageKeeperException(string("user not found with login =" + error_text)){}
};

class UnexpectedError:public MessageKeeperException{
public:
    UnexpectedError(const string& error_text): MessageKeeperException(string("unexpected error: " + error_text)){}
};