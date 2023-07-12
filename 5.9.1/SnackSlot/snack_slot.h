#pragma once
#include <vector>
#include <string>
#include "../Snack/snack.h"

using std::vector;

class SnackSlot{
public:
    SnackSlot() = default;
    SnackSlot(unsigned int max_size);
    SnackSlot(unsigned int max_size, unsigned int size, Snack* snack_array);
    SnackSlot(const SnackSlot& other);

    SnackSlot& operator=(const SnackSlot &other);

    bool addSnacks(unsigned int size, const Snack* const snack_array, std::string &error_text);
    bool addSnack(const Snack& snack, std::string &error_text);
    bool addSnack(const Snack* const snack);

    unsigned int fullness() const;

    unsigned int getMaxSize() const;

    bool expandMaximumCapacity(unsigned int new_max_capacity);

    Snack* PopSnack(std::string &error_text);

    bool Empty() const;
    ~SnackSlot();

private:
    unsigned int max_size;
    unsigned int current_size;
    Snack* storage;
};


