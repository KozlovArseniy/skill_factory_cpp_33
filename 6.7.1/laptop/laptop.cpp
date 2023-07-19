//
// Created by arseniy on 17.07.23.
//
#include "laptop.h"
#include <iostream>

using std::cout, std::endl, std::string, std::to_string;

void Laptop::Show(){
    cout<<"Vendor gpu this laptop is " + this->_gpu_vendor<<".\n"<<
    "Price this laptop is " + to_string( this->GetPrice())<<endl;
}

Laptop::~Laptop(){
    cout<<"Destructor of Laptop"<<endl;
}

string Laptop::GetGpuVendor(){
    return this->_gpu_vendor;
}
