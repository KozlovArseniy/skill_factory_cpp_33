#include <iostream>
#include "Array/array_exceptions.h"
#include "Array/array.h"

int main() {
    try{
        Array <int>(-10);
    }
    catch (ArrayExceptionErrorSize const & e){
        std::cout<<e.what()<<std::endl;
    }

    Array<float> b(3);
    b.push_back(14);
    b.push_front(13);
    b.push_front(12);
    b.push_front(11);
    b.push_back(15);
    std::cout<<b<<std::endl;

    Array c = b;

    std::cout<<c<<std::endl;
    std::cout<<c[2]<<std::endl;

    c.resize(12);
    std::cout<<c<<std::endl;

    try{
        std::cout<<c[7]<<std::endl;
    }
    catch (const ArrayExceptionErrorIndex &e){
        std::cout<<e.what()<<std::endl;
    }

    std::cout<<c.find(13)<<std::endl;

    try{
        std::cout<<c.find(133)<<std::endl;
    }
    catch (const ArrayExceptionElementNotFound &e){
        std::cout<<e.what()<<std::endl;
    }
//
//    c.remove(3);
//    std::cout<<c<<std::endl;
    return 0;
}
