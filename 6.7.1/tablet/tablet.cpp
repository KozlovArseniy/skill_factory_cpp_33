//
// Created by arseniy on 19.07.23.
//

#include "tablet.h"
#include <iostream>

using std::cout, std::endl, std::string, std::to_string;


void Tablet::Show(){
    cout<<"MultiTouch count of this tablet is  " + to_string(this->_multi_touch_count)<<".\n"<<
        "Price this tablet is " + to_string( this->GetPrice())<<endl;
}
Tablet::~Tablet(){
    cout<<"Destructor of Tablet"<<endl;
}

unsigned int Tablet::GetMultiTouchCount(){
    return this->_multi_touch_count;
}