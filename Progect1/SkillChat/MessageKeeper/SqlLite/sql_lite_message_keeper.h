//
// Created by arseniy on 10.08.23.
//
#pragma once

#include "../message_keeper.h"
#include "sqlite3.h"
#include "../MessageKeeperException/message_keeper_exception.h"

class SqlLiteMessageKeeper: public MessageKeeper{
public:
    SqlLiteMessageKeeper();
    ~SqlLiteMessageKeeper() override;
    void AddNewUser(const User& user) override;
    User LoginUser(const string& login, const string& password) override;
    void SendMessageToUserByLogin( const string &current_login, const string &other_login, const Message &msg ) override;
    vector<Message> GetAllMessageByLogin( const string &current_login, const string &other_login ) override;
    vector<Message> ReadAllUnreadMessage( const string &current_login ) override;
    void SetUnreadMessage( const Message &msg ) override;
    void SetReadMessage( const Message &msg ) override;
private:
    void Open();
    void CreateStructure();
    int GetUserId( const string &login );
    void ChangeReadState( const Message &msg, bool read );

    template<typename T>
    void RunSqlRequest( const string& request, T exception, int (*callback)(void*,int,char**,char**) = nullptr, void* user_args = nullptr );

    static int CallBackSearchUser( void *user_args, int argc, char **argv, char **azColName );
    static int CallBackGetMessages( void *user_args, int argc, char **argv, char **azColName );
    static int StringToInt( const string &str );
    static inline string _default_name = "char_db";
    sqlite3* _data_base_connection;
};
