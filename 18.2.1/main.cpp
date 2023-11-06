#include <iostream>
#include <fstream>
#include <vector>
#include "data_classes.h"
#include "file_lib.h"

using std::endl, std::cout, std::ifstream, std::vector;

int main() {
    vector<User> user_info;
    if( !ParseConfigUserFile("user_config", user_info) ){
        cout << "Не удалось разобрать данные о пользователях" << '\n';
        return 1;
    }

    vector<Message> message_info;
    if( !ParseConfigMessageFile("message_config", message_info) ){
        cout << "Не удалось разобрать данные о сообщениях" << '\n';
        return 1;
    }

    if( !CreateConfigUserFile("new_user_config", user_info) ){
        cout << "Не удалось записать конфиг о пользователях" << '\n';
        return 1;
    }

    if( !CreateConfigMessageFile("new_message_config", message_info) ){
        cout << "Не удалось записать конфиг о сообщениях" << '\n';
        return 1;
    }

    return 0;
}
