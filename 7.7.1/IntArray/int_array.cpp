//
// Created by arseniy on 26.07.23.
//

#include <iostream>
#include "int_array.h"
#include "int_array_exceptions.h"


IntArray::IntArray(int max_size){
    if( max_size < 0 )
        throw IntArrayExceptionErrorSize("constructor.");
    this->_max_size = max_size;
    try {
        this->_array = new int[this->_max_size];
    }
    catch (std::bad_alloc const &e){
        throw IntArrayException("In constructor. There is not enough memory for the class instance.");
    }
}

IntArray::IntArray(const IntArray &other){
    try {
        this->_array = new int[other._max_size];
    }
    catch (std::bad_alloc const &e){
        throw IntArrayException("In constructor. There is not enough memory for the class instance.");
    }
    this->_max_size = other._max_size;
    this->_current_size = other._current_size;
    for( int i = 0; i < this->_current_size; ++i ){
        this->_array[i] = other._array[i];
    }
}

IntArray::~IntArray(){
    std::cout<<"IntArray destructor"<<std::endl;
    delete[] this->_array;
}

int& IntArray::operator[](int index){
    if ( index < 0)
        throw IntArrayExceptionErrorIndex("operator [], index < 0.");
    if ( index >= this->_current_size )
        throw IntArrayExceptionErrorIndex("operator [], index > current_size.");
    return this->_array[index];
}

IntArray& IntArray::operator=(const IntArray &other){
    if(this == &other)
        return *this;
    try{
        this->resize(other._max_size);
    }
    catch (const IntArrayExceptionErrorSize &e){
    }
    this->_current_size = other._current_size;
    this->_max_size = other._max_size;
    for(int i = 0; i < this->_current_size; ++i){
        this->_array[i] = other._array[i];
    }
    return *this;
}

void IntArray::push_back(int new_element){
    if( this->_current_size >= this->_max_size)
        this->resize(this->_max_size + 1 + (this->_max_size / 5)); /// + 20%
    this->_array[this->_current_size] = new_element;
    this->_current_size ++;
}

void IntArray::push_front(int new_element){
    if( this->_current_size >= this->_max_size)
        this->resize(this->_max_size + 1 + (this->_max_size / 5)); /// + 20%
    for(int i = this->_current_size; i > 0; --i){
        this->_array[i] = this->_array[i-1];
    }
    this->_array[0] = new_element;
    this->_current_size ++;
}

int IntArray::find(int element) const{
    for(int i = 0;i < this->_current_size; ++i){
        if( this->_array[i] == element )
            return i;
    }
    throw IntArrayExceptionElementNotFound(element);
}

void IntArray::remove(int index){
    if ( index < 0)
        throw IntArrayExceptionErrorIndex("operator [], index < 0.");
    if ( index >= this->_current_size )
        throw IntArrayExceptionErrorIndex("operator [], index > current_size.");
    for( int i = index; i < this->_current_size-1; ++i ){
        this->_array[i] = this->_array[i+1];
    }
    this->_current_size--;
}

void IntArray::resize(int new_max_size){
    if( new_max_size == this->_max_size )
        return;
    if( new_max_size < this->_max_size )
        throw IntArrayExceptionErrorSize("resize. new_max_size < max_size");
    int* tmp;
    try {
        tmp = new int[new_max_size];
    }
    catch (std::bad_alloc const &e){
        delete tmp;
        throw IntArrayException("In resize. There is not enough memory for resize instance.");
    }
    this->_max_size = new_max_size;
    for(int i = 0; i < this->_current_size; ++i){
        tmp[i] = this->_array[i];
    }
    delete[] this->_array ;
    this->_array = tmp;
}

std::ostream &operator<<(std::ostream &output, const IntArray &arr ){
    output<<"Max size = " + std::to_string(arr._max_size) <<"\n";
    output<<"Current size = " + std::to_string(arr._current_size) <<"\n";
    for( int i = 0; i < arr._current_size; ++i)
        output<<std::to_string(arr._array[i]) + " ";
    return output;
}
