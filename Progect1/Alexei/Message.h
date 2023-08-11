#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<ctime>
#include"User.h"

class Message
{
public:
    time_t now = time(0); // current date/time based on current system

    Message(const std::string& text, User* sender, User* recipient);

    void setText(const std::string& text);

    const std::string& getText() const;

    const std::string& getSender() const;

    const std::string& getRecipient() const;

    const std::string& getSendinDatetime() const;

    friend std::ostream& operator<<(std::ostream& os, const Message& m);

private:
    std::string _UUID;
    std::string _text;
    std::string _sender;
    std::string _recipient;
    std::string _sendinDatetime;
};


