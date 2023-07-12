#include <iostream>
#include "vending_machine.h"


VendingMachine::VendingMachine(unsigned int size){
    this->storage = new SnackSlot[size];
    this->max_size = size;
    this->current_size = 0;
}

VendingMachine::~VendingMachine(){

    delete[] this->storage;
    std::cout<<"VendingMachine`s destructor was called"<<std::endl;
}

unsigned int VendingMachine::getEmptySlotsCount(){
    unsigned int result = 0;
    for( size_t i = 0; i < this->current_size; ++i ){
        if( this->storage[i].Empty() )
            ++result;
    }
    return result;
}

bool VendingMachine::addSlot(unsigned int size, const SnackSlot* const slot_array, std::string &error_text){
    if(this->current_size + size > this->max_size){
        error_text = "Slot overload";
        return false;
    }
    for(size_t i = 0; i < size; ++i){
        if( this->storage[this->current_size].getMaxSize() < slot_array[i].getMaxSize())
            this->storage[this->current_size].expandMaximumCapacity(slot_array[i].getMaxSize());
        this->storage[this->current_size] = slot_array[i];
        this->current_size++;
    }
    return true;
}

bool VendingMachine::addSlot(const SnackSlot& slot, std::string &error_text){
    return this->addSlot(1, &slot, error_text);
}

bool VendingMachine::addSlot(const SnackSlot* const slot){
    string error_text = "";
    if( slot == nullptr )
        return false;
    return this->addSlot(*slot, error_text);
}

unsigned int VendingMachine::totalNumberSnacks(){
    unsigned int result = 0;
    for( size_t i = 0; i < this->current_size; ++i )
        result += this->storage[i].fullness();
    return result;
}

Snack* VendingMachine::byFromSlot(unsigned int slot){
    if( slot > this->current_size)
        return nullptr;
    std::string error_text;
    return this->storage[slot].PopSnack(error_text);
}