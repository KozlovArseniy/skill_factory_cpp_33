//
// Created by arseniy on 19.11.23.
//
#include "listener.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

#include <cstring>
#include <unistd.h>

Listener::Listener(int port, int buf_size):_port(port), _stopped(false), _buf_size(buf_size){
    this->_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(this->_socket_fd == -1)
        throw ListenerException("Socket creation failed.!" );

    struct sockaddr_in serveraddress;
    //
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим номер порта для связи
    serveraddress.sin_port = htons(this->_port);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет
    int bind_status = bind(this->_socket_fd, (struct sockaddr*)&serveraddress,
                       sizeof(serveraddress));
    if(bind_status == -1)
        throw ListenerException("Socket binding failed.!" );
    // Поставим сервер на прием данных
    int connection_status = listen(this->_socket_fd, this->_max_connection_count_plus_1);
    if(connection_status == -1)
        throw ListenerException("Socket is unable to listen for new connections.!" );
}

int Listener::get_first_empty( const struct pollfd *fds ) const{
    for(int i = 1; i < this->_max_connection_count_plus_1; ++i)
        if( fds[i].fd == -1)
            return i;
    return -1;
}

void Listener::ThreadRun(){
    this->_thread = new std::thread([this](){ Run(); });
}


void Listener::Run(){
    struct sockaddr_in client;
    unsigned int length = sizeof(client);
    struct pollfd fds[this->_max_connection_count_plus_1];
    fds[0].fd = this->_socket_fd;
    fds[0].events = POLLIN | POLLRDHUP | POLLRDHUP;

    for(int i = 1; i < this->_max_connection_count_plus_1; ++i) {
        fds[i].fd = -1;
        fds[i].events = 0;
        fds[i].revents = 0;
    }
    while( !this->_stopped ){
        int ret = poll( fds, this->_max_connection_count_plus_1, 2000 );
        //std::cout<<ret<<std::endl;
        if( ret == 0 )
            continue;
        if ( fds[0].revents & POLLIN ){ // новое соединение
            fds[0].revents = 0;
            int connection = accept(fds[0].fd,(struct sockaddr*)&client, &length);
            int index_first_empty = this->get_first_empty(fds);
            if( index_first_empty > 0) {
                fds[index_first_empty].fd = connection;
                fds[index_first_empty].revents = 0;
                fds[index_first_empty].events = POLLIN | POLLRDHUP | POLLHUP;
            }
        }
        for(int i = 1; i < this->_max_connection_count_plus_1; ++i)
        {
            if( ( fds[i].revents & POLLRDHUP ) | ( fds[i].revents & POLLHUP ) ){
                close(fds[i].fd);
                fds[i].fd = -1;
                fds[i].events = 0;
            }
            if( fds[i].revents & POLLIN )
            {
                char message[this->_buf_size];
                bzero(message, this->_buf_size);
                read(fds[i].fd, message, sizeof(message));
                string msg_string(message);
                if( !msg_string.empty() )
                    printf("INCOMING MSG: %s\n", msg_string.c_str());
            }
            fds[i].revents = 0;
        }

    }
}

void Listener::Stop(){
    this->_stopped = true;
    this->_thread->join();
}