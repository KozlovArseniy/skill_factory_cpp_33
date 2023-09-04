//
// Created by arseniy on 10.08.23.
//
#pragma once

#include <exception>
#include <string>

using std::string;

class ChatException: public std::exception{
public:
    ChatException(const string& error_text): _error_text( string("Exception from Chat ") + error_text){}
    ChatException(const ChatException& chat_exception);
    void AppendText( const string& error_text );
    const char * what() const noexcept override;
private:
    string _error_text;
};


class NotImplementedException: public std::exception{
public:
    NotImplementedException(const string& error_text): _error_text( string("NotImplementedException: ") + error_text){}
    const char * what() const noexcept override;
private:
    string _error_text;
};