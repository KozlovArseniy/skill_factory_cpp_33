//
// Created by arseniy on 14.08.23.
//
#pragma once
#include <string>

using std::string;

class User {
public:
    User();
    User(const string &name, const string &login, const string &password);
    User(const string &name, const string &login, const string &password, bool loggedin);
    User(const User& other_user);

    User& operator=(const User& other_user);

    User& operator=(User&& move);

    void SetLoggedIn(bool logged_in);

    string GetName() const;
    string GetLogin() const;
    string GetPassword() const;
    bool IsLoggedIn() const;

private:
    string _name;
    string _login;
    string _password;
    bool _logged_in;
};
