#pragma once
#include <iostream>
#include <typeinfo>
#include "./reflect/classRegister.h"
#include "./reflect/Object.h"
class B: public object_t {
public:
    B() = default;
    ~B()= default;
    void show() {
        std::cout << typeid(*this).name() << std::endl;
    }
};

REGISTER_CLASS(B);
