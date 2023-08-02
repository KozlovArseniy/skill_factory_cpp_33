//
// Created by arseniy on 26.07.23.
//
#pragma once

#include <exception>
#include <string>

using std::string;

class ArrayException: public std::exception{
public:
    ArrayException(const string& error_text): _error_text( string("Exception from IntArrayException. ") + error_text){}
    const char * what() const noexcept override;
    ~ArrayException() {}
private:
    string _error_text;
};

class ArrayExceptionErrorSize: public ArrayException{
public:
    ArrayExceptionErrorSize(const string& error_text): ArrayException(string("Bad size in ") + error_text){}
};

class ArrayExceptionErrorIndex: public ArrayException{
public:
    ArrayExceptionErrorIndex(string error_text): ArrayException(string("Error index in ") + error_text){}
};

class ArrayExceptionElementNotFound: public ArrayException{ /// Натянуто, но елси не так, то можно возвращать nullpt, но там int, поэтому nullptr не вернуть
                                                                  /// считаем, что чаще всего ищут значения, которые есть в массиве
public:
    ArrayExceptionElementNotFound(int element): ArrayException(std::to_string(element) + " Not found."){}
};