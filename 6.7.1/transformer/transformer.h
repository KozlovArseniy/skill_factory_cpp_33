//
// Created by arseniy on 19.07.23.
//
#pragma once
#include "../laptop/laptop.h"
#include "../tablet/tablet.h"


class Transformer final:  public Tablet, Laptop{
public:
    Transformer(unsigned int price, string gpu_vendor, unsigned int multi_touch_count, unsigned int ports_count):
        IElectronics(price),
        Laptop(price, gpu_vendor),
        Tablet(price, multi_touch_count),
        _ports_count(ports_count){}
    void Show() override;
    ~Transformer() override;
private:
    unsigned int _ports_count;
};
