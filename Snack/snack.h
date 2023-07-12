#pragma once

#include <string>
using std::string;

class Snack {
public:
    Snack() = default;
    Snack(const string &name);
    Snack(const string &name, unsigned int price);
    Snack(const string &name, unsigned int price, unsigned int calories);
    Snack(const Snack &old_snack);
    ~Snack();

    unsigned int GetPrice() const;
    void SetPrice(unsigned int new_price);

    string GetName() const;
    void SetName(const string &new_name);

    unsigned int GetCalories() const;
    void SetCalories(unsigned int new_calories);


private:
    unsigned int price;
    string name;
    unsigned int calories;
};


