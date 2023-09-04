//
// Created by arseniy on 23.08.23.
//
#include <iostream>
#include "console_ui.h"
#include "../../MessageKeeper/MessageKeeperException/message_keeper_exception.h"

using std::cout, std::cin, std::cerr, std::endl;


ConsoleUi::ConsoleUi():Ui(){}

UserCommands ConsoleUi::GetUserCommand(){
    cout<<"Введите номер нужной операции:\n";
    int inputted_command = 0;
    if( !this->_current_user.IsLoggedIn() )
        cout<<"     1) Войти в SkillChat\n"
            <<"     2) Зарегистрироваться в SkillChat\n";
    else {
        cout << "     1) Выйти из SkillChat\n"
             << "     2) Прочитать все непрочитанные сообщения\n"
             << "     3) Написать сообщение\n"
             << "     4) Получить все сообщения с собеседником\n";
        inputted_command = 10;
    }
    cout<<"     q) Закрыть приложение\n"<<endl;
    string input;
    cin>>input;
    if( "q" == input )
        return UserCommands(-1);

    try{
        inputted_command += stoi(input);
    }
    catch (const std::invalid_argument& e )
    {
        cout<<"Вы должны ввести целое число, а не строку. Вы ввели: " + input;
    }
    return UserCommands(inputted_command);
}

void ConsoleUi::MainLoop(){
    cout<<"Добро пожаловать в SkillChat\n";
    bool working = true;
    while (working){
        UserCommands inputted_command = GetUserCommand();
        switch (inputted_command) {
            case UserCommands_Exit:{
                working = false;
                break;
            }
            case UserCommands_Login:{
                this->LoginWindow();
                break;
            }
            case UserCommands_Register:{
                this->RegisterWindow();
                break;
            }
            case UserCommands_Logout:{
                this->_current_user.SetLoggedIn(false);
                cout<<"Вы вышли из SkillChat\n"<<endl;
                break;
            }
            case UserCommands_ReadUnread:{
                this->ReadUnReadWindow();
                break;
            }
            case UserCommands_Write:{
                this->WriteLetterWindow();
                break;
            }
            case UserCommands_ReadCorrespondence:{
                this->GetCorrespondenceWindow();
                break;
            }
            default:{
                cout<<"Вы ввели неожиданную команду, выберите корректную команду из списка.\n\n"<<endl;
                break;
            }
        }

    }
    cout<<"Выход..."<<endl;
}

void ConsoleUi::LoginWindow(){
    string password, login;
    cout<<"Введите Ваш логин"<<endl;
    cin>>login;
    cout<<"Введите Ваш пароль"<<endl;
    cin>>password;
    try {
        this->_current_user = std::move(this->_message_keeper->LoginUser(login, password));
    }
    catch (const UserNotFoundException &e){
        cerr<<"\nОшибка или в логине или в пароле.\n"<<endl;
        return;
    }
    catch (const UnexpectedError &e){
        cerr<<"\nПроизошла неизвестая ошибка при входе.\n"<<endl;
        return;
    }
    cout<<"Вы успешно вошли в SkillChat \n" <<endl;
}

void ConsoleUi::RegisterWindow() {
    string name, password, login;
    cout<<"Введите Ваше имя"<<endl;
    cin>>name;
    cout<<"Введите Ваш логин"<<endl;
    cin>>login;
    cout<<"Введите Ваш пароль"<<endl;
    cin>>password;

    User new_user = User(name, login, password);
    try {
        this->_message_keeper->AddNewUser(new_user);
    }
    catch (const CannotCreateNewUserException &e){
        cerr<<"\nПользователь с таким логином уже существует, введите другой логин.\n"<<endl;
        return;
    }
    new_user.SetLoggedIn(true);
    this->_current_user = std::move(new_user);
    cout<<"Поздравляем, Вы зарегистрировались в SkillChat \n" <<endl;
}

void ConsoleUi::WriteLetterWindow(){
    string login, message;
    cout<<"Введите логин собеседника"<<endl;
    cin>>login;
    cout<<"Введите сообщение"<<endl;
    std::getline(cin, message); ///Вычитываем мусор после cin>>login
    std::getline(cin, message);
    Message msg(message, this->_current_user.GetLogin(), login);
    try {
        this->_message_keeper->SendMessageToUserByLogin(this->_current_user.GetLogin(), login, msg);
    } catch (const UserNotFoundException& e)
    {
        cerr<<"Адресат не найден, письмо не удалось отправить"<<endl;
        return;
    } catch (const UnexpectedError& e)
    {
        cerr<<"Во время отправки произошла непредвиденная ошибка"<<endl;
        return;
    }
    cout<<"Сообщение успешно отправлено"<<endl;
}

void ConsoleUi::ReadUnReadWindow() {
    vector<Message> msgs;
    try{
       msgs = this->_message_keeper->ReadAllUnreadMessage(this->_current_user.GetLogin());
    }
    catch( const UnexpectedError& e) {
        cerr<<"Произошла неожиднная ошибка при получении непрочитанных сообщений"<<endl;
    }
    for( const auto& el: msgs)
        cout<<el<<endl;
}

void ConsoleUi::GetCorrespondenceWindow() {
    string other_login;
    cout<<"Введите логин собеседника"<<endl;
    cin>>other_login;
    vector<Message> msgs;
    try{
        msgs = this->_message_keeper->GetAllMessageByLogin(this->_current_user.GetLogin(), other_login);
    }
    catch( const UnexpectedError& e) {
        cerr<<"Произошла неожиднная ошибка при получении непрочитанных сообщений"<<endl;
    }
    for( const auto& el: msgs)
        cout<<el<<endl;
}
