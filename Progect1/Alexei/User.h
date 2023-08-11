#pragma once
#include<string>

class User
{
public:
    User(const std::string& name);

    std::string getName();

private:
    std::string _name;
};
