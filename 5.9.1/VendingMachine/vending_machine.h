#pragma once

#include "../SnackSlot/snack_slot.h"

class VendingMachine{
public:
    VendingMachine() = default;
    VendingMachine(unsigned int size);

    ~VendingMachine();

    unsigned int getEmptySlotsCount();

    unsigned int totalNumberSnacks();

    bool addSlot(unsigned int size, const SnackSlot* const snack_array, std::string &error_text);
    bool addSlot(const SnackSlot& snack, std::string &error_text);
    bool addSlot(const SnackSlot* const slot);

    Snack* byFromSlot(unsigned int slot);

private:
    unsigned int max_size;
    unsigned int current_size;
    SnackSlot* storage;
};