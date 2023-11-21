//
// Created by arseniy on 21.11.23.
//
#include <sys/socket.h>
#include <arpa/inet.h>
#include "sender.h"
#include <unistd.h>


Sender::Sender(int port): _port(port){}

void Sender::Run(){
    printf("Добро пожаловть в чат!\n");
    string addr, msg;
    char addr_c_str[20], msg_c_str[100];
    int socket_fd;
    while (true){
        printf("Введите IP адрес собеседника или end для выхода\n");

        scanf("%s", addr_c_str);
        addr = string(addr_c_str);
        if( addr.find(string("end") ) != std::string::npos )
            break;
        printf("Введите сообщение:\n");

        scanf("%s", msg_c_str);
        msg = string(msg_c_str);
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(socket_fd == -1)
            throw SenderException("Socket creation failed.!" );

        struct sockaddr_in serveraddress;
        serveraddress.sin_addr.s_addr = inet_addr(addr.c_str());
        serveraddress.sin_port = htons(this->_port);
        serveraddress.sin_family = AF_INET;
        int connection = connect(socket_fd, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
        if(connection == -1){
            printf("Сервер недоступен, возможно, указан неверный адрес\n");
            continue;
        }
        ssize_t bytes = write(socket_fd, msg.c_str(), msg.size() );
        if( bytes > 0 )
            printf("Сообщение доставлено\n");
        else
            printf("Во время отправки сообещния произошла ошибка, повторите попыту позже\n");
        close(socket_fd);
    }

}