//
// Created by arseniy on 26.07.23.
//
#pragma once

#include "array_exceptions.h"

template<typename T>
class Array {
public:
    Array(int max_size){
        if( max_size < 0 )
            throw ArrayExceptionErrorSize("constructor.");
        this->_max_size = max_size;
        this->_current_size = 0;
        try {
            this->_array = new T[this->_max_size];
        }
        catch (std::bad_alloc const &e){
            throw ArrayException("In constructor. There is not enough memory for the class instance.");
        }
    }
    Array(const Array &other){
        try {
            this->_array = new T[other._max_size];
        }
        catch (std::bad_alloc const &e){
            throw ArrayException("In constructor. There is not enough memory for the class instance.");
        }
        this->_max_size = other._max_size;
        this->_current_size = other._current_size;
        for( int i = 0; i < this->_current_size; ++i ){
            this->_array[i] = other._array[i];
        }
    }
    T& operator[](int index){
        if ( index < 0)
            throw ArrayExceptionErrorIndex("operator [], index < 0.");
        if ( index >= this->_current_size )
            throw ArrayExceptionErrorIndex("operator [], index > current_size.");
        return this->_array[index];
    }
    Array& operator=(const Array &other){
        if(this == &other)
            return *this;
        try{
            this->resize(other._max_size);
        }
        catch (const ArrayExceptionErrorSize &e){
        }
        this->_current_size = other._current_size;
        this->_max_size = other._max_size;
        for(int i = 0; i < this->_current_size; ++i){
            this->_array[i] = other._array[i];
        }
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &output, const Array &arr ){
        output<<"Max size = " + std::to_string(arr._max_size) <<"\n";
        output<<"Current size = " + std::to_string(arr._current_size) <<"\n";
        for( int i = 0; i < arr._current_size; ++i)
            output<<std::to_string(arr._array[i]) + " ";
        return output;
    }
    void push_back(T new_element){
        if( this->_current_size >= this->_max_size)
            this->resize(this->_max_size + 1 + (this->_max_size / 5)); /// + 20%
        this->_array[this->_current_size] = new_element;
        this->_current_size ++;
    }
    void push_front(T new_element){
        if( this->_current_size >= this->_max_size)
            this->resize(this->_max_size + 1 + (this->_max_size / 5)); /// + 20%
        for(int i = this->_current_size; i > 0; --i){
            this->_array[i] = this->_array[i-1];
        }
        this->_array[0] = new_element;
        this->_current_size ++;
    }
    void resize(int new_max_size){
        if( new_max_size == this->_max_size )
            return;
        if( new_max_size < this->_max_size )
            throw ArrayExceptionErrorSize("resize. new_max_size < max_size");
        T* tmp;
        try {
            tmp = new T[new_max_size];
        }
        catch (std::bad_alloc const &e){
            delete tmp;
            throw ArrayException("In resize. There is not enough memory for resize instance.");
        }
        this->_max_size = new_max_size;
        for(int i = 0; i < this->_current_size; ++i){
            tmp[i] = this->_array[i];
        }
        delete[] this->_array ;
        this->_array = tmp;
    }
    T find(T element) const{
        for(int i = 0;i < this->_current_size; ++i){
            if( this->_array[i] == element )
                return i;
        }
        throw ArrayExceptionElementNotFound(element);
    }
    void remove(int index){
        if ( index < 0)
            throw ArrayExceptionErrorIndex("operator [], index < 0.");
        if ( index >= this->_current_size )
            throw ArrayExceptionErrorIndex("operator [], index > current_size.");
        for( int i = index; i < this->_current_size-1; ++i ){
            this->_array[i] = this->_array[i+1];
        }
        this->_current_size--;
    }
    ~Array(){
        std::cout<<"Array destructor"<<std::endl;
        delete[] this->_array;
    }

private:
    int _max_size, _current_size;
    T *_array;
};
