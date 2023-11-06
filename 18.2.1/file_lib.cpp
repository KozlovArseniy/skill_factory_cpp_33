//
// Created by arseniy on 06.11.23.
//
#include "file_lib.h"
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

using std::string, std::endl, std::cout, std::ifstream, std::vector, std::ofstream;

bool ParseUserInfoStr(const string &str, vector<User> &user_info ){
    User tmp;
    size_t end_name = str.find(',');
    if( end_name > str.length() ){
        return false;
    }
    tmp._name = str.substr(0, end_name);

    size_t end_login = str.substr(end_name+1, str.length()).find(',');
    if( end_login > str.length() ){
        return false;
    }
    tmp._login = str.substr(end_name+1, end_login);
    tmp._pass = str.substr(end_name + 1 + end_login + 1, str.length());
    user_info.push_back( tmp );
    return true;
}

bool ParseConfigUserFile(const string &file_config, vector<User> &user_info){
    ifstream user_readr( "../" + file_config );

    if( !user_readr.is_open() ){
        cout << "Не удалось открыть файл с конфигурацией пользователей" << '\n';
        return false;
    }
    string line;
    while( !user_readr.eof() ){
        getline(user_readr, line);
        if( line.empty() )
            break;
        cout<<line<<endl;
        if( !ParseUserInfoStr( line, user_info ) ){
            cout << "Ошибка при парсинге файла конфигурации о пользователе" << '\n';
            return false;
        }
        line.clear();
    }
    user_readr.close();
    return true;
}

bool ParseMessageInfoStr(const string &str, vector<Message> &message_info){
    Message tmp;
    size_t end_text = str.find(',');
    if(end_text > str.length() ){
        return false;
    }
    tmp._text = str.substr(0, end_text);

    size_t end_sender = str.substr(end_text+1, str.length()).find(',');
    if(end_sender > str.length() ){
        return false;
    }
    tmp._sender = str.substr(end_text + 1, end_sender);
    tmp._receiver = str.substr(end_text + 1 + end_sender + 1, str.length());
    message_info.push_back( tmp );
    return true;
}

bool ParseConfigMessageFile(const string &file_config, vector<Message> &message_info){
    ifstream message_reader( "../" + file_config );

    if( !message_reader.is_open() ){
        cout << "Не удалось открыть файл с конфигурацией пользователей" << '\n';
        return false;
    }
    string line;
    while( !message_reader.eof() ){
        getline(message_reader, line);
        if( line.empty() )
            break;
        cout<<line<<endl;
        if( !ParseMessageInfoStr( line, message_info ) ){
            cout << "Ошибка при парсинге файла конфигурации о пользователе" << '\n';
            return false;
        }
        line.clear();
    }
    message_reader.close();
    return true;
}

bool CreateConfigUserFile(const string &file_config, const vector<User> &user_info){
    ofstream out_stream("../" + file_config);
    if( !out_stream.is_open() ){
        cout<<"Не удалось открыть файл для записи конфига о пользователях"<<endl;
        return false;
    }
    for(auto & it : user_info)
        out_stream<<it._name<<","<<it._login<<","<<it._pass<<endl;
    out_stream.close();
    fs::permissions("../" + file_config, std::filesystem::perms::owner_write | std::filesystem::perms::owner_read );
    return true;
}

bool CreateConfigMessageFile(const string &file_config, const vector<Message> &message_info){
    ofstream out_stream("../" + file_config);
    if( !out_stream.is_open() ){
        cout<<"Не удалось открыть файл для записи конфига о сообщениях"<<endl;
        return false;
    }
    for(auto & it : message_info)
        out_stream<<it._text<<","<<it._sender<<","<<it._receiver<<endl;
    out_stream.close();
    fs::permissions("../" + file_config, std::filesystem::perms::owner_write | std::filesystem::perms::owner_read );
    return true;
}
