//
// Created by arseniy on 17.07.23.
//
#pragma once
#include <string>
#include "../sold_electronics/sold_electronics.h"

using std::string;

class Laptop: virtual public SoldElectronics{
public:
    Laptop(unsigned int price, string gpu_vendor) :IElectronics(price), _gpu_vendor(gpu_vendor){}
    void Show() override;
    ~Laptop() override;
    string GetGpuVendor();
private:
    string _gpu_vendor;
};