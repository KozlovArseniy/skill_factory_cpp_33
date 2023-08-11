#include"User.h"

User::User(const std::string& name) : _name(name) {}

std::string User::getName() { return _name; }