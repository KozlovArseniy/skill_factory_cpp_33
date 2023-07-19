//
// Created by arseniy on 19.07.23.
//
#pragma once
#include "../sold_electronics/sold_electronics.h"


class Tablet : virtual public SoldElectronics{
public:
    Tablet(unsigned int price, unsigned int multi_touch_count) :IElectronics(price), _multi_touch_count(multi_touch_count){}
    void Show() override;
    ~Tablet() override;
    unsigned int GetMultiTouchCount();
private:
    unsigned int _multi_touch_count;
};
