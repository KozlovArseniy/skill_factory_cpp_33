//
// Created by arseniy on 10.08.23.
//

#include "sql_lite_message_keeper.h"

#include <iostream>

using std::cout, std::endl;

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
    auto* user_struct = static_cast<SqlResponseSearchUser*>(user_args);
    user_struct->user_id = StringToInt(string(argv[0]));
    user_struct->name = string(argv[1]);
    user_struct->login = string(argv[2]);
    user_struct->password = string(argv[3]);

    return 0;
}

int SqlLiteMessageKeeper::CallBackGetMessages(void *user_args, int argc, char **argv, char **azColName){
    if (argc == 0)
        return 0;

    SqlResponseGetMessage tmp = {string(argv[0]),
                                 StringToInt(
                                         string(argv[1])),
                                 string(argv[2]),
                                 static_cast<bool>(StringToInt(
                                         string(argv[3]))),
                                 string(argv[4])
    };
    if(argc == 6) /// Если дергаем для получения переписки с отдельным человеком
        tmp.receiver = string(argv[5]);
    static_cast<vector<SqlResponseGetMessage>*>(user_args)->push_back(tmp);
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
    string sql_request ("UPDATE \"Message\" SET \"Read\" = " + value_to_insert + " WHERE \"Uuid\" = '" + msg.GetUuid() + "';");
    this->RunSqlRequest( sql_request, UnexpectedError(""));
}

int SqlLiteMessageKeeper::GetUserId(const string &login){
    string sql_request ("SELECT * FROM \"User\" WHERE \"Login\" = '"+ login +"' ");

    SqlResponseSearchUser user_sender{0};
    this->RunSqlRequest( sql_request, UnexpectedError(""), SqlLiteMessageKeeper::CallBackSearchUser, &user_sender);
    return user_sender.user_id;
}

void SqlLiteMessageKeeper::Open() {
    if (sqlite3_open((SqlLiteMessageKeeper::_default_name + string (".dblite")).c_str(), &this->_data_base_connection) != SQLITE_OK) {
        string error_text (sqlite3_errmsg(this->_data_base_connection));
        throw CannotOpenMessageKeeperException(error_text);
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
        throw CannotCreateStructureException(error_str);
    }
}

void SqlLiteMessageKeeper::SendMessageToUserByLogin( const string &current_login, const string &other_login, const Message &msg){
    int sender_id = this->GetUserId(current_login);
    int receiver_id = this->GetUserId(other_login);
    if( sender_id == 0 || receiver_id == 0) /// не найден один из участников беседы
        throw UserNotFoundException(string("sender or receiver not found."));
    string str_sender = std::to_string(sender_id);
    string str_receiver = std::to_string(receiver_id);

    string sql_request ("INSERT INTO \"Message\""
                        "(\"Sender\", \"Receiver\", \"Body\", \"DateTimeOfSend\", \"Uuid\", \"Read\") "
                        "VALUES ('" + str_sender + "', '" + str_receiver +
                        "', '" + msg.GetText() + "', ""'" + std::to_string(msg.GetSendingDatetime()) + "', '" +
                        msg.GetUuid() + "', '0');");
    this->RunSqlRequest( sql_request, UnexpectedError(""));
}


vector<Message> SqlLiteMessageKeeper::GetAllMessageByLogin( const string &current_login, const string &other_login ){
    vector<Message> result;
    int sender_id = SqlLiteMessageKeeper::GetUserId(current_login);
    int receiver_id = SqlLiteMessageKeeper::GetUserId(other_login);
    string str_sender = std::to_string(sender_id);
    string str_receiver = std::to_string(receiver_id);
    string sql_request( "SELECT \"Body\", \"DateTimeOfSend\", \"Uuid\", \"Read\", sender.\"Login\" Sender, receiver.\"Login\" Receiver FROM \"Message\" "
                        "LEFT JOIN \"User\" sender ON \"Sender\" = sender.\"@User\" LEFT JOIN \"User\" receiver ON \"Receiver\" = receiver.\"@User\"  "
                        "WHERE (\"Sender\" = " + str_sender + " AND \"Receiver\" = " + str_receiver + " ) or "
                         "(\"Sender\" = " + str_receiver + " AND \"Receiver\" = " + str_sender + " ) ORDER BY \"DateTimeOfSend\"; " );

    vector<SqlResponseGetMessage> sql_result;
    this->RunSqlRequest( sql_request, UnexpectedError(""), SqlLiteMessageKeeper::CallBackGetMessages, &sql_result);
    result.reserve(sql_result.size());
    for(const SqlResponseGetMessage& it: sql_result)
        result.emplace_back(it.body, current_login, other_login, it.date_time_of_send, it.uuid);

    return result;
}


vector<Message> SqlLiteMessageKeeper::ReadAllUnreadMessage( const string &current_login ){
    vector<Message> result;
    int receiver_id = SqlLiteMessageKeeper::GetUserId(current_login);
    string str_receiver = std::to_string(receiver_id);
    string sql_request( "SELECT \"Body\", \"DateTimeOfSend\", \"Uuid\", \"Read\", \"Login\" FROM \"Message\" "
                        "LEFT JOIN \"User\" ON \"Sender\" = \"@User\" WHERE \"Read\" = 0 AND \"Receiver\" = " + str_receiver + ";");

    vector<SqlResponseGetMessage> sql_result;
    this->RunSqlRequest( sql_request, UnexpectedError(""), SqlLiteMessageKeeper::CallBackGetMessages, &sql_result);

    result.reserve(sql_result.size());
    for(const SqlResponseGetMessage& it: sql_result) {
        result.emplace_back(it.body, it.sender, current_login, it.date_time_of_send, it.uuid);
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
    this->RunSqlRequest( sql_request, CannotCreateNewUserException(""));
}

User SqlLiteMessageKeeper::LoginUser(const string& login, const string& password) {
    string sql_request ("SELECT * FROM \"User\" WHERE \"Login\" = '"+ login +"' AND \"Password\" = '" + password +"' ");

    SqlResponseSearchUser user_sender{0};
    user_sender.user_id = -1; /// Невозможный user id
    this->RunSqlRequest( sql_request, UnexpectedError(""), SqlLiteMessageKeeper::CallBackSearchUser, &user_sender);
    if( user_sender.user_id == -1 )
        throw UserNotFoundException("Not found user.");
    return {user_sender.name, user_sender.login, user_sender.password, true};
}

template<typename T>
void SqlLiteMessageKeeper::RunSqlRequest( const string& request, T exception, int (*callback)(void*,int,char**,char**), void* user_args ){
    char* error_text;
    if (sqlite3_exec(this->_data_base_connection, request.c_str(), callback, user_args, &error_text) != SQLITE_OK){
        string error_str(error_text); /// в sqlite3_exec динамическое выделение памяти, копируем
        /// данные в string, чтобы корректно освободить память error_text
        sqlite3_free(error_text);
        exception.AppendText(error_str);
        throw exception;
    }
}