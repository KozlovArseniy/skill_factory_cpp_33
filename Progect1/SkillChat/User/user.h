//
// Created by arseniy on 14.08.23.
//
#pragma once
#include <string>

using std::string;

class User {
public:
    User(string name, string login, string password);

    string GetName() const;
    string GetLogin() const;
    string GetPassword() const;

private:
    string _name;
    string _login;
    string _password;
};
