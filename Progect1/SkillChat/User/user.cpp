//
// Created by arseniy on 14.08.23.
//

#include "user.h"

User::User(){};

User::User(const string &name, const string &login, const string &password): _login(login), _name(name), _password(password), _logged_in(false) {};
User::User(const string &name, const string &login, const string &password, bool loggedin): _login(login), _name(name), _password(password), _logged_in(loggedin) {};

User::User(const User& other_user){
    if (this == &other_user)
        return;

    this->_logged_in = other_user._logged_in;
    this->_password = other_user._password;
    this->_login = other_user._login;
    this->_name = other_user._name;
}

User& User::operator=(const User& other_user){
    if (this == &other_user)
        return *this;

    this->_logged_in = other_user._logged_in;
    this->_password = other_user._password;
    this->_login = other_user._login;
    this->_name = other_user._name;
    return *this;
}

User& User::operator=(User&& move){
    if( this == &move)
        return *this;

    this->_logged_in = move._logged_in;
    this->_password = move._password;
    this->_login = move._login;
    this->_name = move._name;

    move._logged_in = false;
    move._name.clear();
    move._login.clear();
    move._password.clear();

    return *this;
}

string User::GetName() const{
    return this->_name;
}

string User::GetLogin() const{
    return this->_login;
}

string User::GetPassword() const{
    return this->_password;
}

bool User::IsLoggedIn() const{
    return this->_logged_in;
}

void User::SetLoggedIn(bool logged_in){
    this->_logged_in = logged_in;
}