#pragma once
#include <string>
using namespace std;

class User
{
	static int userCounter;
	int _id;
	string _login;
	string _username;
    string _password;
public:
	User();
    User(string username, string passHash);
    int checklogin(const string& login, const string& passHash) const;
	string& getuserName();
	int getUserID() const;
};
