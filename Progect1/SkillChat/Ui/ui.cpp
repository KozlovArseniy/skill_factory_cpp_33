//
// Created by arseniy on 23.08.23.
//
#include "ui.h"
#include "../MessageKeeper/MessageKeeperException/message_keeper_exception.h"

#ifdef SQL_LITE
    #include "../MessageKeeper/SqlLite/sql_lite_message_keeper.h"
#elif FILE_MESSAGE_KEEPER
    #include /// подключем файл где реализовано хранение сообщений в виде файла txt
#endif


Ui::Ui(){
    this->_current_user = User();
    try {
#ifdef SQL_LITE
        this->_message_keeper = new SqlLiteMessageKeeper();
#elif FILE_MESSAGE_KEEPER
        this->_message_keeper = new FileMessageKeeper();
#endif
    } catch (MessageKeeperException const &e){
        throw ChatException("Failed to connect to message store.");
    }
}

void Ui::MainLoop(){
    throw NotImplementedException("Ui::MainLoop");
}

void Ui::LoginWindow() {
    throw NotImplementedException("Ui::LoginWindow");
}

void Ui::RegisterWindow(){
    throw NotImplementedException("Ui::RegisterWindow");
}

void Ui::WriteLetterWindow() {
    throw NotImplementedException("Ui::WriteLetterWindow");
}

void Ui::ReadUnReadWindow() {
    throw NotImplementedException("Ui::ReadUnReadWindow");
}

void Ui::GetCorrespondenceWindow() {
    throw NotImplementedException("Ui::GetCorrespondenceWindow");
}
