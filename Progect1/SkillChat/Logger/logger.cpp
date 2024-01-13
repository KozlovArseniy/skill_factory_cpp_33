//
// Created by arseniy on 13.01.24.
//
#include <iostream>
#include "logger.h"
#include "../Exception/chat_exception.h"

Logger::~Logger() {
    std::cout<<"Destroy logger"<<std::endl;
    std::lock_guard<mutex> destroy_lock(this->_logger_mutex );
    _main_logger_stream.close();
}

Logger& Logger::Instance(){
    static Logger result;
    std::call_once(result._initialized, &Logger::InitLogStream, result);
    return result;
}

void Logger::WriteLog( const string &log_msg, LogLevel log_level ){
    time_t ltime;
    time(&ltime);
    string msg = string( ctime(&ltime) );
    msg = msg.substr(0, msg.size() - 1 );
    switch (log_level) {
        case InfoMsg:{
            msg += "  Info  " + log_msg;
            break;
        }
        case WarningMsg:
        {
            msg += "  WarningMsg  " + log_msg;
            break;
        }
        case ErrorMsg:
        {
            msg += "  ErrorMsg  " + log_msg;
            break;
        }
        default:{
            throw ChatException("Не верный формат логирования");
        }
    }
    return this->WriteStrToFile( msg );
}

void Logger::WriteStrToFile( const string& log_msg ){
    std::lock_guard<mutex> write_lock(this->_logger_mutex );
    this->_main_logger_stream<<log_msg<<std::endl;
}

void Logger::InitLogStream(){
    std::cout<<"Init logger"<<std::endl;
    this->_main_logger_stream.open(this->log_file_name, std::ios::app| std::ios::out );
    if( !this->_main_logger_stream.is_open() )
        throw ChatException("Не удалось открыть файл для лога");
}