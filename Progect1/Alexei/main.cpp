
//Message demo

#include"Message.h"

int main()
{
    User u1("Vanya");
    User u2("Goga");
    Message m1("Hi, Goga!", &u1, &u2);
    std::cout << m1 << std::endl;
}