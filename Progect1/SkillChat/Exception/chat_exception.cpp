//
// Created by arseniy on 10.08.23.
//

#include "chat_exception.h"

const char * ChatException::what() const noexcept{
    return this->_error_text.c_str();
}

ChatException::ChatException(const ChatException& chat_exception){
    this->_error_text = chat_exception._error_text;
}

void ChatException::AppendText( const string& error_text ){
    this->_error_text += " " + error_text;
}