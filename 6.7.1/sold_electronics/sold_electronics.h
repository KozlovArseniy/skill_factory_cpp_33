//
// Created by arseniy on 19.07.23.
//
#pragma once
#include "../electronics/electronics.h"

class SoldElectronics: virtual public IElectronics {
public:
    SoldElectronics(unsigned int price): IElectronics(price){}
    SoldElectronics() = default;
    ~SoldElectronics();
    void Show();
};
