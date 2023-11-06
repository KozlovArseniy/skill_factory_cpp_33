//
// Created by arseniy on 06.11.23.
//
#pragma once

#include <string>
using std::string;

class User{
public:
    string _name;
    string _login;
    string _pass;
};

class Message{
public:
    string _text;
    string _sender;
    string _receiver;
};