//
// Created by arseniy on 14.08.23.
//

#include "user.h"

User::User(string name, string login, string password): _login(login), _name(name), _password(password){}

string User::GetName() const{
    return this->_name;
}

string User::GetLogin() const{
    return this->_login;
}

string User::GetPassword() const{
    return this->_password;
}
