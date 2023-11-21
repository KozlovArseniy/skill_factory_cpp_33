//
// Created by arseniy on 19.11.23.
//
#pragma once

#include <exception>
#include <string>
#include <thread>

using std::string;

class ListenerException: public std::exception{
public:
    ListenerException(const string& error_text): _error_text( string("Exception from ListenerException: ") + error_text){}
    ListenerException(const ListenerException& listener_exception);
private:
    string _error_text;
};


class Listener{
public:
    Listener(int port, int buf_size);
    void Run();
    void ThreadRun();
    void Stop();

private:
    int get_first_empty( const struct pollfd *fds ) const;

    int _socket_fd;
    int _port;
    int _buf_size;
    bool _stopped;
    std::thread* _thread;

    static inline int _max_connection_count_plus_1 = 2;
};