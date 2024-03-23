#include "User.h"
int User::userCounter = 1;

User::User() : _id(0), _login(""), _username(""), _password()
{
}

User::User(string username, string passHash) :_login(username), _username(username), _password(passHash), _id(++userCounter)
{
}

int User::checklogin(const string& login, const string& passHash) const
{
    if ((_login == login) && (_password == passHash)) return _id;
	return -1;
}

string& User::getuserName() 
{
	return _username;
}

int User::getUserID() const
{
	return _id;
}
