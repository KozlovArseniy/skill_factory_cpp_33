//
// Created by arseniy on 23.08.23.
//
#pragma once
#include "../ui.h"

enum UserCommands{
    UserCommands_Exit = -1,
    UserCommands_Login = 1,
    UserCommands_Register = 2,
    UserCommands_Logout = 11,
    UserCommands_ReadUnread = 12,
    UserCommands_Write = 13,
    UserCommands_ReadCorrespondence = 14,
};

class ConsoleUi: public Ui{
public:
    ConsoleUi();
    void MainLoop() override;
    void LoginWindow() override;
    void RegisterWindow() override;
    void WriteLetterWindow() override;
    void ReadUnReadWindow() override;
    void GetCorrespondenceWindow() override;

private:
    UserCommands GetUserCommand();

};
