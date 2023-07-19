//
// Created by arseniy on 19.07.23.
//

#include "sold_electronics.h"
#include <iostream>

using std::cout, std::endl, std::string, std::to_string;

void SoldElectronics::Show(){
    cout<<"Price of this product is " + to_string(this->GetPrice())<<endl;
}

SoldElectronics::~SoldElectronics(){
    cout<<"Destructor of SoldElectronics"<<endl;
}