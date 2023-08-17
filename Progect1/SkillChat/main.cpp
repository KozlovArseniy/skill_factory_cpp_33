#include <iostream>
#include <chrono>
#include "sqlite3.h"

#include "sqlite3.h"
#include "MessageKeeper/SqlLite/sql_lite_message_keeper.h"


int main() {
    SqlLiteMessageKeeper a;

    const time_t t_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    Message msg("hi", "Vas", "Pet", t_c);
    User us("Pet", "Pet", "da");
    User us1("Vas", "Vas", "da");
    a.AddNewUser(us);
    a.AddNewUser(us1);
    Message msg1("hidqwdqwd", "Vas", "Pet", t_c);
    a.SendMessageToUserByLogin("Vas", "Pet", msg);
    a.SendMessageToUserByLogin("Vas", "Pet", msg1);
    a.SetReadMessage(msg);
    a.SetUnreadMessage(msg);

    vector<Message> msgs = a.GetAllMessageByLogin("Vas", "Pet");


    std::cout<<msgs.back().getUuid()<<std::endl;
    return 0;
}
