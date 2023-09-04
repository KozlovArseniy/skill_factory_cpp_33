//
// Created by arseniy on 10.08.23.
//
#pragma once

#include "string"

using std::string;

class Message {
public:
    Message(const std::string& text, const std::string& sender, const std::string& receiver, time_t time);

    Message(const std::string& text, const std::string& sender, const std::string& receiver);

    Message(const std::string& text, const std::string& sender, const std::string& receiver, time_t time, const std::string& uuid );

    friend std::ostream &operator<<(std::ostream &output, const Message &msg );

    void SetText(const std::string& text);

    const std::string& GetText() const;

    const std::string& GetSender() const;

    const std::string& GetRecipient() const;

    const std::string& GetUuid() const;

    time_t GetSendingDatetime() const;
private:
    static string UuidGen();

    string _UUID;
    string _text;
    string _sender;
    string _recipient;
    time_t _sendinDatetime;
};
