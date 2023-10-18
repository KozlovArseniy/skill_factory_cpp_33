//
// Created by arseniy on 10.08.23.
//

#include "message.h"
#include <stdlib.h>

Message::Message(const std::string& text, const std::string& sender, const std::string& receiver, time_t time) : _text(text), _sender(sender), _recipient(receiver), _sendinDatetime(time) {
    this->_UUID = Message::UuidGen();
}

Message::Message(const std::string& text, const std::string& sender, const std::string& receiver, time_t time, const std::string& uuid) : _text(text), _sender(sender), _recipient(receiver), _sendinDatetime(time), _UUID(uuid) {}

Message::Message(const string &text, const string &sender, const string &receiver): _text(text), _sender(sender), _recipient(receiver){
    time_t now;
    time(&now);
    this->_sendinDatetime = now;
    this->_UUID = Message::UuidGen();
}

std::ostream &operator<<(std::ostream &output, const Message &msg ){
    output<<"Отправитель - " + msg._sender + "\n";
    output<<"Получатель - " + msg._recipient + "\n";
    struct tm *now = localtime(&msg._sendinDatetime);
    char datetime[21]; ///"%d:%d:%d  %d.%d.%d0"
    sprintf(datetime, "%d:%d:%d  %d.%d.%d", now->tm_hour, now->tm_min, now->tm_sec, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    output<<"Время получения - " + string(datetime) + "\n";
    output<<"Текст  - " + msg._text + "\n";
    return output;
}

void Message::SetText(const std::string& text) { _text = text; }

const std::string& Message::GetText() const { return _text; }

const std::string& Message::GetSender() const { return _sender; }

const std::string& Message::GetRecipient() const { return _recipient; }

time_t Message::GetSendingDatetime() const { return _sendinDatetime; }

const std::string& Message::GetUuid()const{ return _UUID; }

string Message::UuidGen() {
    srand(time(NULL));
    string abc{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    string ans;
    int min = 100, max = 5000; /// пределы случайного илса для енерации UUID
    int num = min + rand() % (max - min + 1);
    while(num > 0){
        ans += abc[num % 10];
        num /=10;
    }
    return ans;
}