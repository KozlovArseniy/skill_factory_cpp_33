
#include <iostream>
#include "snack.h"

Snack::Snack(const string &name, unsigned int price){
    this->name = name;
    this->price = price;
    this->calories = 0;
}

Snack::Snack(const string &name){
    this->name = name;
    this->price = 0;
    this->calories = 0;
}

Snack::Snack(const string &name, unsigned int price, unsigned int calories){
    this->name = name;
    this->price = price;
    this->calories = calories;
}

Snack::Snack(const Snack &old_snack){
    this->calories = old_snack.calories;
    this->price = old_snack.price;
    this->name = old_snack.name;
}

Snack::~Snack(){
   std::cout<<"Snack`s destructor was called "<<std::endl;
}

unsigned int Snack::GetPrice() const{
    return this->price;
}

void Snack::SetPrice(unsigned int new_price){
    this->price = new_price;
}

string Snack::GetName() const{
    return this->name;
}

void Snack::SetName(const std::string &new_name){
    this->name = new_name;
}

unsigned int Snack::GetCalories() const{
    return this->calories;
}

void Snack::SetCalories(unsigned int new_calories){
    this->calories = new_calories;
}