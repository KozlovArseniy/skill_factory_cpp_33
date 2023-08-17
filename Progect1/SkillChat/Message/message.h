//
// Created by arseniy on 10.08.23.
//
#pragma once

#include "string"

using std::string;

class Message {
public:
    Message(const std::string& text, const std::string& sender, const std::string& recipient, time_t time);

    Message(const std::string& text, const std::string& sender, const std::string& recipient, time_t time, const std::string& uuid );

    void setText(const std::string& text);

    const std::string& getText() const;

    const std::string& getSender() const;

    const std::string& getRecipient() const;

    const std::string& getUuid() const;

    time_t getSendinDatetime() const;
private:
    std::string _UUID;
    std::string _text;
    std::string _sender;
    std::string _recipient;
    time_t _sendinDatetime;
};
