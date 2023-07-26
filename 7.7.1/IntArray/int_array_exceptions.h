//
// Created by arseniy on 26.07.23.
//
#pragma once

#include <exception>
#include <string>

using std::string;

class IntArrayException: public std::exception{
public:
    IntArrayException(const string& error_text): _error_text( string("Exception from IntArrayException. ") + error_text){}
    const char * what() const noexcept override;
    ~IntArrayException() {}
private:
    string _error_text;
};

class IntArrayExceptionErrorSize: public IntArrayException{
public:
    IntArrayExceptionErrorSize(const string& error_text): IntArrayException(string("Bad size in ") + error_text){}
};

class IntArrayExceptionErrorIndex: public IntArrayException{
public:
    IntArrayExceptionErrorIndex(string error_text): IntArrayException(string("Error index in ") + error_text){}
};

class IntArrayExceptionElementNotFound: public IntArrayException{ /// Натянуто, но елси не так, то можно возвращать nullpt, но там int, поэтому nullptr не вернуть
                                                                  /// считаем, что чаще всего ищут значения, которые есть в массиве
public:
    IntArrayExceptionElementNotFound(int element): IntArrayException(std::to_string(element) + " Not found."){}
};