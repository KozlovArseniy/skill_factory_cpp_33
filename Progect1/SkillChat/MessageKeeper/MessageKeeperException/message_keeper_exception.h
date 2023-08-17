//
// Created by arseniy on 10.08.23.
//
#pragma once

#include "../../Exception/chat_exception.h"

class MessageKeeperException :public ChatException{
public:
    MessageKeeperException(const string& error_text): ChatException(string("from MessageKeeper ") + error_text){}
};

