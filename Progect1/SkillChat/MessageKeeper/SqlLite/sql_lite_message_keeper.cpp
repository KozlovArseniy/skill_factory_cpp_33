//
// Created by arseniy on 10.08.23.
//

#include "sql_lite_message_keeper.h"

#include <iostream>

using std::cout, std::endl;

struct SqlResponseSearchUser{
    int user_id;
};

struct SqlResponseGetMessage{
    string body;
    int date_time_of_send;
    string uuid;
    bool read;
};

int SqlLiteMessageKeeper::StringToInt(const string &str){
    int result = 0;
    for( const char& it:str ) {
        result *= 10;
        result += it - '0';
    }
    return result;
}

int SqlLiteMessageKeeper::CallBackSearchUser(void *user_args, int argc, char **argv, char **azColName){
    if (argc == 0)
        return 0;
    static_cast<SqlResponseSearchUser*>(user_args)->user_id = StringToInt(string(argv[0]));
    return 0;
}

int SqlLiteMessageKeeper::CallBackGetMessages(void *user_args, int argc, char **argv, char **azColName){
    if (argc == 0)
        return 0;

    static_cast<vector<SqlResponseGetMessage>*>(user_args)->push_back(SqlResponseGetMessage{string(argv[0]),
                                                                                            StringToInt(
                                                                                                    string(argv[1])),
                                                                                            string(argv[2]),
                                                                                            static_cast<bool>(StringToInt(
                                                                                                    string(argv[3])))
    });
    return 0;
}

SqlLiteMessageKeeper::SqlLiteMessageKeeper(){
    this->_data_base_connection = nullptr;
    this->Open();
    this->CreateStructure();
}

SqlLiteMessageKeeper::~SqlLiteMessageKeeper(){
    sqlite3_close(this->_data_base_connection);
}

void SqlLiteMessageKeeper::ChangeReadState(const Message &msg, bool read){
    string value_to_insert = string((read)? "1" : "0");
    string sql_request ("UPDATE \"Message\" SET \"Read\" = " + value_to_insert +" WHERE \"Uuid\" = '" + msg.getUuid() + "';");
    this->RunSqlRequest( sql_request, SqliteUnexpectedError(""));
}

int SqlLiteMessageKeeper::GetUserId(const string &login){
    string sql_request ("SELECT \"@User\" FROM \"User\" WHERE \"Login\" = '"+ login +"' ");

    SqlResponseSearchUser user_sender{0};
    this->RunSqlRequest( sql_request, SqliteUnexpectedError(""), SqlLiteMessageKeeper::CallBackSearchUser, &user_sender);
    return user_sender.user_id;
}

void SqlLiteMessageKeeper::Open() {
    if (sqlite3_open((SqlLiteMessageKeeper::_default_name + string (".dblite")).c_str(), &this->_data_base_connection) != SQLITE_OK) {
        string error_text (sqlite3_errmsg(this->_data_base_connection));
        throw SqliteCannotOpenDataBaseException(error_text);
    }
}

void SqlLiteMessageKeeper::CreateStructure(){
    char* error_text;
    string create_user_table = "CREATE TABLE if not exists \"User\" (\n"
                               "\t\"@User\"\tINTEGER NOT NULL UNIQUE,\n"
                               "\t\"Name\"\tTEXT NOT NULL,\n"
                               "\t\"Login\"\tTEXT NOT NULL UNIQUE,\n"
                               "\t\"Password\"\tTEXT NOT NULL,\n"
                               "\tPRIMARY KEY(\"@User\" AUTOINCREMENT)\n"
                               ");";

    string create_message_table = "CREATE TABLE if not exists \"Message\" (\n"
                                  "\t\"@Message\"\tINTEGER NOT NULL UNIQUE,\n"
                                  "\t\"Sender\"\tINTEGER NOT NULL,\n"
                                  "\t\"Receiver\"\tINTEGER NOT NULL,\n"
                                  "\t\"Body\"\tTEXT NOT NULL,\n"
                                  "\t\"DateTimeOfSend\"\tINTEGER NOT NULL,\n"
                                  "\t\"Uuid\"\tTEXT NOT NULL,\n"
                                  "\t\"Read\"\tINTEGER,\n"
                                  "\tPRIMARY KEY(\"@Message\" AUTOINCREMENT)\n"
                                  ");";
    if (sqlite3_exec(this->_data_base_connection, create_user_table.c_str(), nullptr, nullptr, &error_text) != SQLITE_OK
        ||sqlite3_exec(this->_data_base_connection, create_message_table.c_str(), nullptr, nullptr, &error_text) != SQLITE_OK
    )
    {
        string error_str(error_text); /// в sqlite3_exec динамическое выделение памяти, копируем
                                         /// данные в string, чтобы корректно освободить память error_text
        sqlite3_free(error_text);
        sqlite3_close(this->_data_base_connection);
        throw SqliteCannotCreateStructureException(error_str);
    }
}

void SqlLiteMessageKeeper::SendMessageToUserByLogin( string current_login, string other_login, const Message &msg){
    int sender_id = this->GetUserId(current_login);
    int receiver_id = this->GetUserId(other_login);
    if( sender_id == 0 || receiver_id == 0) /// не найден один из участников беседы
        throw SqliteUserNotFoundException(string("sender or receiver not found."));
    string str_sender = std::to_string(sender_id);
    string str_receiver = std::to_string(receiver_id);

    string sql_request ("INSERT INTO \"Message\""
                        "(\"Sender\", \"Receiver\", \"Body\", \"DateTimeOfSend\", \"Uuid\", \"Read\") "
                        "VALUES ('" + str_sender+ "', '"+ str_receiver+
                        "', '"+ msg.getText()+"', ""'"+ std::to_string(msg.getSendinDatetime())+"', '"+msg.getUuid()+"', '0');");
    this->RunSqlRequest( sql_request, SqliteUnexpectedError(""));
}


vector<Message> SqlLiteMessageKeeper::GetAllMessageByLogin( string current_login, string other_login ){
    vector<Message> result;
    int sender_id = SqlLiteMessageKeeper::GetUserId(current_login);
    int receiver_id = SqlLiteMessageKeeper::GetUserId(other_login);
    string str_sender = std::to_string(sender_id);
    string str_receiver = std::to_string(receiver_id);
    string sql_request( "SELECT \"Body\", \"DateTimeOfSend\", \"Uuid\", \"Read\" FROM \"Message\" WHERE"
                       " \"Sender\" = " + str_sender + " AND \"Receiver\" = " + str_receiver + ";");

    vector<SqlResponseGetMessage> sql_result;
    this->RunSqlRequest( sql_request, SqliteUnexpectedError(""), SqlLiteMessageKeeper::CallBackGetMessages, &sql_result);
    result.reserve(sql_result.size());
    for(const SqlResponseGetMessage& it: sql_result)
        result.emplace_back(it.body, current_login, other_login, it.date_time_of_send, it.uuid);

    return result;
}


vector<Message> SqlLiteMessageKeeper::ReadAllUnreadMessage( string current_login, string other_login ){
    vector<Message> result;
    int receiver_id = SqlLiteMessageKeeper::GetUserId(other_login);
    string str_receiver = std::to_string(receiver_id);
    string sql_request( "SELECT \"Body\", \"DateTimeOfSend\", \"Uuid\", \"Read\" FROM \"Message\" WHERE"
                        " \"Read\" = 0 AND \"Receiver\" = " + str_receiver + ";");

    vector<SqlResponseGetMessage> sql_result;
    this->RunSqlRequest( sql_request, SqliteUnexpectedError(""), SqlLiteMessageKeeper::CallBackGetMessages, &sql_result);

    result.reserve(sql_result.size());
    for(const SqlResponseGetMessage& it: sql_result) {
        result.emplace_back(it.body, current_login, other_login, it.date_time_of_send, it.uuid);
        this->SetReadMessage(result.back());
    }

    return result;
}

void SqlLiteMessageKeeper::SetUnreadMessage( const Message &msg ){
    return this->ChangeReadState(msg, false);
}

void SqlLiteMessageKeeper::SetReadMessage( const Message &msg ){
    return this->ChangeReadState(msg, true);
}

void SqlLiteMessageKeeper::AddNewUser(const User &user) {
    string sql_request ("INSERT INTO \"User\"(\"Login\", \"Name\", \"Password\") "
                        "VALUES ('" + user.GetLogin()+ "', '"+ user.GetName()+"', '"+user.GetPassword()+"');");
    this->RunSqlRequest( sql_request, SqliteCannotCreateNewUserException(""));
}

void SqlLiteMessageKeeper::RunSqlRequest( const string& request, SqlLiteException exception, int (*callback)(void*,int,char**,char**), void* user_args ){
    char* error_text;
    if (sqlite3_exec(this->_data_base_connection, request.c_str(), callback, user_args, &error_text) != SQLITE_OK){
        string error_str(error_text); /// в sqlite3_exec динамическое выделение памяти, копируем
        /// данные в string, чтобы корректно освободить память error_text
        sqlite3_free(error_text);
        exception.AppendText(error_str);
        throw exception;
    }
}