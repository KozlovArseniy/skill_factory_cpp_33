//
// Created by arseniy on 19.07.23.
//

#include "transformer.h"
#include <iostream>

using std::cout, std::endl, std::string, std::to_string;

void Transformer::Show(){
    cout<<"MultiTouch count of this transformer is  " + to_string(this->GetMultiTouchCount())<<".\n"<<
          "GpuVendor of this transformer is  " + this->GetGpuVendor()<<".\n"<<
          "PortCounts of this transformer is  " + to_string(this->_ports_count)<<".\n"<<
          "Price this tablet is " + to_string( this->GetPrice())<<endl;
}

Transformer::~Transformer(){
    cout<<"Destructor of Transformer"<<endl;
}