//
// Created by arseniy on 23.08.23.
//
#pragma once

#include <string>
#include "../User/user.h"
#include "../MessageKeeper/message_keeper.h"

using std::string;

class Ui {
public:
    Ui();
    virtual void MainLoop();
    virtual void LoginWindow();
    virtual void RegisterWindow();
    virtual void WriteLetterWindow();
    virtual void ReadUnReadWindow();
    virtual void GetCorrespondenceWindow();

protected:
    User _current_user;
    MessageKeeper* _message_keeper;
};


