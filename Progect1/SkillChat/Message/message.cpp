//
// Created by arseniy on 10.08.23.
//

#include "message.h"

Message::Message(const std::string& text, const std::string& sender, const std::string& receiver, time_t time) : _text(text), _sender(sender), _recipient(receiver), _sendinDatetime(time) {
    this->_UUID = "uuid1";
}

Message::Message(const std::string& text, const std::string& sender, const std::string& receiver, time_t time, const std::string& uuid) : _text(text), _sender(sender), _recipient(receiver), _sendinDatetime(time), _UUID(uuid) {}

void Message::setText(const std::string& text) { _text = text; }

const std::string& Message::getText() const { return _text; }

const std::string& Message::getSender() const { return _sender; }

const std::string& Message::getRecipient() const { return _recipient; }

time_t Message::getSendinDatetime() const { return _sendinDatetime; }

const std::string& Message::getUuid()const{ return _UUID; }