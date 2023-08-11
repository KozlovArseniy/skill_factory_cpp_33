#include "Message.h"

Message::Message(const std::string& text, User* sender, User* recipient) : _text(text), _sender(sender->getName()), _recipient(recipient->getName()), _sendinDatetime(ctime(&now)) {}

void Message::setText(const std::string& text) { _text = text; }

const std::string& Message::getText() const { return _text; }

const std::string& Message::getSender() const { return _sender; }

const std::string& Message::getRecipient() const { return _recipient; }

const std::string& Message::getSendinDatetime() const { return _sendinDatetime; }

std::ostream& operator<<(std::ostream& os, const Message& m)
{
    return os << "Message from: " << m.getSender() << "\nto: " << m.getRecipient() << "\nmessage text: " << m.getText() << "\nsending time: " << m.getSendinDatetime();
}