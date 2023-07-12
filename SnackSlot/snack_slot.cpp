#include <iostream>
#include "snack_slot.h"

SnackSlot::SnackSlot(unsigned int max_size){
    this->max_size = max_size;
    this->current_size = 0;
    this->storage = new Snack[this->max_size];
}

SnackSlot::SnackSlot(unsigned int max_size, unsigned int size, Snack* snack_array){
    this->max_size = max_size;
    this->current_size = size;
    this->storage = new Snack[this->max_size];
    for( size_t i = 0; i < size; ++i ){
        this->storage[i] = snack_array[i];
    }
}

SnackSlot::SnackSlot(const SnackSlot& other){
    std::cout<<"Copy constructor called"<<std::endl;
    this->current_size = other.current_size;
    this->max_size = other.max_size;
    this->storage = new Snack[this->max_size];
    for( size_t i = 0; i < max_size; ++i ){
        this->storage[i] = other.storage[i];
    }
}

SnackSlot::~SnackSlot(){
    delete[] this->storage;
    std::cout<<"SnackSlot`s destructor was called"<<std::endl;
}

SnackSlot& SnackSlot::operator= (const SnackSlot &other){
    std::cout<<"SnackSlot`s overloaded ="<<std::endl;
    this->current_size = other.current_size;
    this->max_size = other.max_size;
    for( size_t i = 0; i < this->current_size; ++i){
        this->storage[i] = other.storage[i];
    }
    return *this;
}

bool SnackSlot::expandMaximumCapacity(unsigned int new_max_capacity){
    Snack* new_storage = new Snack[new_max_capacity];
    for( size_t i = 0; i < this->current_size; ++i){
        new_storage[i] = this->storage[i];
    }
    this->max_size = new_max_capacity;
    delete[] this->storage;
    this->storage = new_storage;
    return true;
}

bool SnackSlot::addSnacks(unsigned int size, const Snack* const snack_array, std::string &error_text){
    if(this->current_size + size > this->max_size){
        error_text = "Slot overload";
        return false;
    }
    for(size_t i = 0; i < size; ++i){
        this->storage[this->current_size] = snack_array[i];
        this->current_size++;
    }
    return true;
}

bool SnackSlot::addSnack(const Snack& snack, std::string &error_text){
    return this->addSnacks(1, &snack,error_text);
}

bool SnackSlot::addSnack(const Snack* const snack){
    string error_text = "";
    if( snack == nullptr )
        return false;
    return this->addSnack(*snack, error_text);
}

unsigned int SnackSlot::getMaxSize() const{
    return this->max_size;
}

unsigned int SnackSlot::fullness() const{
    return this->current_size;
}

Snack* SnackSlot::PopSnack(std::string &error_text){
    if(this->current_size == 0){
        error_text = "Slot empty";
        return nullptr;
    }
    Snack* value = new Snack(this->storage[this->current_size-1]);
    return value;
}

bool SnackSlot::Empty() const{
    return this->current_size == 0;
}
