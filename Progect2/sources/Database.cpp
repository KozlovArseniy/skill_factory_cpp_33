#include "Database.h"
#include "Parsing.h"
#include <memory>
#include <iostream>>


template<typename T>
void Database::RunSqlRequest( const string& request, T exception, int (*callback)(void*,int,char**,char**), void* user_args ) const{
    char* error_text;
    if (sqlite3_exec(this->_data_base_connection, request.c_str(), callback, user_args, &error_text) != SQLITE_OK){
        string error_str(error_text); /// в sqlite3_exec динамическое выделение памяти, копируем
        /// данные в string, чтобы корректно освободить память error_text
        sqlite3_free(error_text);
        std::cout<<"basd_sql = " + request<<std::endl;
        exit(1);
    }
}


int Database::StringToInt(const string &str){
    int result = 0;
    for( const char& it:str ) {
        result *= 10;
        result += it - '0';
    }
    return result;
}

int Database::CallBackGetMessages(void *user_args, int argc, char **argv, char **azColName){
    std::cout<<"call back argc = " + to_string(argc)<<std::endl;
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

int Database::CallBackGetUsers(void *user_args, int argc, char **argv, char **azColName){
    if (argc == 0)
        return 0;
    SqlResponseSearchUser tmp = {StringToInt(string(argv[0])),
                                  string(argv[1]),
                                  string(argv[2]),
                                 string(argv[3])
    };

    static_cast<vector<SqlResponseSearchUser>*>(user_args)->push_back(tmp);
    return 0;
}


vector<string> Database::getUserList() const
{
    string sql_request ("SELECT * FROM \"User\" ");

    vector<SqlResponseSearchUser> users;
    this->RunSqlRequest( sql_request, std::exception(), Database::CallBackGetUsers, &users);

    vector<string> userList;
    for(auto user : users)
    {
        userList.push_back(user.login);
    }
    return userList;
}


string Database::getUserName(int userId) const
{
    string sql_request ("SELECT * FROM \"User\" WHERE \"@User\" = "+ std::to_string(userId) +" ");

    vector<SqlResponseSearchUser> users;
    this->RunSqlRequest( sql_request, std::exception(), Database::CallBackGetUsers, &users);

    for(auto user : users)
    {
        return user.login;
    }
    return "";
}


int Database::searchUserByName(string username)
{
    string sql_request ("SELECT * FROM \"User\" WHERE \"Login\" = '"+ username +"' ");

    vector<SqlResponseSearchUser> users;
    this->RunSqlRequest( sql_request, std::exception(), Database::CallBackGetUsers, &users);

    for(auto user : users)
    {
        return user.user_id;
    }
    return -1;
}


void Database::Open() {
    if (sqlite3_open((Database::_default_name + string (".dblite")).c_str(), &this->_data_base_connection) != SQLITE_OK) {
        string error_text (sqlite3_errmsg(this->_data_base_connection));
        exit(1);
    }
}


void Database::CreateStructure(){
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
                                  "\t\"Receiver\"\tINTEGER,\n"
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
        exit(1);
    }
}


Database::Database()
{
    this->_data_base_connection = nullptr;
    this->Open();
    this->CreateStructure();
}


Database::~Database()
{
    sqlite3_close(this->_data_base_connection);
}

int Database::addUser(string username, string password)
{
    if (!correctName(username)) return -1;

    if( searchUserByName(username) > 0) return -2;

    string sql_request ("INSERT INTO \"User\"(\"Login\", \"Name\", \"Password\") "
                            "VALUES ('" +username+ "', '"+ username+"', '"+password+"');");
    this->RunSqlRequest( sql_request, std::exception());

    return searchUserByName(username);
}

int Database::checkPassword(string username, string password)
{
    string sql_request ("SELECT * FROM \"User\" WHERE \"Login\" = '"+ username +"' AND \"Password\" = '" + password +"' ");

    vector<SqlResponseSearchUser> users;
    this->RunSqlRequest( sql_request, std::exception(), Database::CallBackGetUsers, &users);
    for(auto user : users)
    {
        return user.user_id;
    }
    return -1;
}

void Database::addChatMessage(string sender, string text)
{
    string str_sender = std::to_string(this->searchUserByName(sender));
    time_t now;
    time(&now);

    string sql_request ("INSERT INTO \"Message\""
                        "(\"Sender\", \"Receiver\", \"Body\", \"DateTimeOfSend\", \"Uuid\", \"Read\") "
                        "VALUES ('" + str_sender + "', NULL, '" + text + "', ""'" + std::to_string(now) + "', 'random uuid', '0');");
    this->RunSqlRequest( sql_request, std::exception());
}

bool Database::addPrivateMessage(string sender, string target, string message)
{
    string str_sender = std::to_string(this->searchUserByName(sender));
    int receiver_id = this->searchUserByName(target);
    if( receiver_id == -1) /// не найден один из участников беседы
        return false;
    string str_receiver = std::to_string(receiver_id);
    time_t now;
    time(&now);

    string sql_request ("INSERT INTO \"Message\""
                        "(\"Sender\", \"Receiver\", \"Body\", \"DateTimeOfSend\", \"Uuid\", \"Read\") "
                        "VALUES ('" + str_sender + "', '" + str_receiver +
                        "', '" + message + "', ""'" + std::to_string(now) + "', 'random uuid', '0');");
    this->RunSqlRequest( sql_request, std::exception());
    return true;
}

vector<string> Database::getChatMessages()
{
    vector<string> result;
    string sql_request( "SELECT \"Body\", \"DateTimeOfSend\", \"Uuid\", \"Read\", sender.\"Login\" Sender FROM \"Message\" "
                        "LEFT JOIN \"User\" sender ON \"Sender\" = sender.\"@User\" WHERE \"Receiver\" IS NULL ORDER BY \"DateTimeOfSend\"; " );

    vector<SqlResponseGetMessage> sql_result;
    this->RunSqlRequest( sql_request, std::exception(), Database::CallBackGetMessages, &sql_result);
    result.reserve(sql_result.size());
    for (auto &m: sql_result)
    {
        result.push_back("<" + m.sender + ">: " + m.body);
    }
    return result;
}

vector<Message> Database::getPrivateMessage(int userID)
{
    vector<Message> result;
    string str_receiver = std::to_string(userID);
    string sql_request( "SELECT \"Body\", \"DateTimeOfSend\", \"Uuid\", \"Read\", sender.\"Login\" Sender, receiver.\"Login\" Receiver FROM \"Message\" "
                        "LEFT JOIN \"User\" sender ON \"Sender\" = sender.\"@User\" LEFT JOIN \"User\" receiver ON \"Receiver\" = receiver.\"@User\"  "
                        "WHERE (\"Receiver\" = " + str_receiver + " ) ORDER BY \"DateTimeOfSend\"; " );

    vector<SqlResponseGetMessage> sql_result;
    this->RunSqlRequest( sql_request, std::exception(), Database::CallBackGetMessages, &sql_result);
    result.reserve(sql_result.size());
    for (auto &m : sql_result)
    {
        result.push_back(Message(m.sender, userID, m.body));
    }
    return result;
}
