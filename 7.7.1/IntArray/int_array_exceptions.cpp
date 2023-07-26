//
// Created by arseniy on 26.07.23.
//

#include "int_array_exceptions.h"

const char * IntArrayException::what() const noexcept{
    return this->_error_text.c_str();
}
