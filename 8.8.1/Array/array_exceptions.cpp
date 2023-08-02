//
// Created by arseniy on 26.07.23.
//

#include "array_exceptions.h"

const char * ArrayException::what() const noexcept{
    return this->_error_text.c_str();
}
