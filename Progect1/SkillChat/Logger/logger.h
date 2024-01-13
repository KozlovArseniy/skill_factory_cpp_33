//
// Created by arseniy on 13.01.24.
//
#pragma once
#include <fstream>
#include <mutex>
#include <string>


using std::ofstream, std::mutex, std::string, std::once_flag;

typedef enum{
    InfoMsg = 0,
    WarningMsg,
    ErrorMsg
} LogLevel;

class Logger{
public:
    Logger()=default;
    static Logger& Instance();
    void WriteLog( const string &log_msg, LogLevel log_level );
    ~Logger();

private:
    void InitLogStream();
    void WriteStrToFile( const string& log_msg );
    ofstream _main_logger_stream;
    string log_file_name = "SkillChat.log";
    once_flag _initialized;
    mutex _logger_mutex;
};