//
// Created by arseniy on 21.11.23.
//
#pragma once

#include <exception>
#include <string>
using std::string;

class SenderException: public std::exception{
public:
    SenderException(const string& error_text): _error_text( string("Exception from SenderException: ") + error_text){}
    SenderException(const SenderException& listener_exception);
private:
    string _error_text;
};

class Sender{
public:
    Sender(int port);
    void Run();

private:
    int _port;
};