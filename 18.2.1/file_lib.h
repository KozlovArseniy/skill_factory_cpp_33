//
// Created by arseniy on 06.11.23.
//
#pragma once
#include <vector>
using std::vector;

#include "data_classes.h"

bool ParseUserInfoStr(const string &str, vector<User> &user_info );

bool ParseConfigUserFile(const string &file_config, vector<User> &user_info);

bool ParseMessageInfoStr(const string &str, vector<Message> &message_info);

bool ParseConfigMessageFile(const string &file_config, vector<Message> &message_info);

bool CreateConfigUserFile(const string &file_config, const vector<User> &user_info);

bool CreateConfigMessageFile(const string &file_config, const vector<Message> &message_info);
