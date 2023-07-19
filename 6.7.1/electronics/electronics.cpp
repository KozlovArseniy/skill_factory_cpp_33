//
// Created by arseniy on 17.07.23.
//
#include "electronics.h"
#include <iostream>

using std::cout, std::endl, std::string, std::to_string;

unsigned int IElectronics::GetPrice(){
    return this->_price;
}

IElectronics::~IElectronics(){
    cout<<"Destructor of IElectronics"<<endl;
}