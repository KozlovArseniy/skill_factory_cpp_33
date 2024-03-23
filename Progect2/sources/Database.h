#pragma once
#include <vector>
#include "User.h"
#include "Message.h"
#include <string>
#include <unordered_map>

#include "sqlite3.h"

struct SqlResponseSearchUser{
    int user_id;
    string login;
    string name;
    string password;
};

struct SqlResponseGetMessage{
    string body;
    int date_time_of_send;
    string uuid;
    bool read;
    string sender;
    string receiver;
};

class Database
{
	int searchUserByName(string);
    static inline string _default_name = "char_db";
    sqlite3* _data_base_connection;
    void Open();
    void CreateStructure();

    static int StringToInt( const string &str );
    static int CallBackGetUsers( void *user_args, int argc, char **argv, char **azColName );
    static int CallBackGetMessages( void *user_args, int argc, char **argv, char **azColName );
    template<typename T>
    void RunSqlRequest( const string& request, T exception, int (*callback)(void*,int,char**,char**) = nullptr, void* user_args = nullptr ) const;


public:

    vector<string> getUserList() const;
    string getUserName(int userId) const;
    Database();
    ~Database();
    int addUser(string username, string password);
    int checkPassword(string username, string password);
    void addChatMessage(string sender, string text);
    bool addPrivateMessage(string sender, string target, string message);
    vector<string> getChatMessages();//показать все сообщения
    vector<Message> getPrivateMessage(int userID = -1);//показать личные сообщения пользователю username
};
