//
// Created by arseniy on 10.08.23.
//
#pragma once
#include "../../MessageKeeperException/message_keeper_exception.h"

class SqlLiteException:public MessageKeeperException{
public:
    SqlLiteException(const string& error_text): MessageKeeperException(string("from SqlLite ") + error_text){}
};

class SqliteCannotOpenDataBaseException:public SqlLiteException{
public:
    SqliteCannotOpenDataBaseException(const string& error_text): SqlLiteException(string("database not opened " + error_text)){}
};

class SqliteCannotCreateStructureException:public SqlLiteException{
public:
    SqliteCannotCreateStructureException(const string& error_text): SqlLiteException(string("cannot create db structure " + error_text)){}
};

class SqliteCannotCreateNewUserException:public SqlLiteException{
public:
    SqliteCannotCreateNewUserException(const string& error_text): SqlLiteException(string("cannot create new user " + error_text)){}
};

class SqliteUserNotFoundException:public SqlLiteException{
public:
    SqliteUserNotFoundException(const string& error_text): SqlLiteException(string("user not found with login =" + error_text)){}
};

class SqliteUnexpectedError:public SqlLiteException{
public:
    SqliteUnexpectedError(const string& error_text): SqlLiteException(string("unexpected error: " + error_text)){}
};