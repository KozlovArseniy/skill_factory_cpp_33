//
// Created by arseniy on 17.07.23.
//

#pragma once

class IElectronics {
public:
    IElectronics(unsigned int price): _price(price){}
    IElectronics() = default;
    virtual ~IElectronics();
    virtual void Show() = 0;
    unsigned int GetPrice();
private:
    unsigned int _price;
};
