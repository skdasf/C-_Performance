#pragma once
#include <string>
#include <iostream>
#include <typeinfo>
#include "./reflect/classRegister.h"
#include "./reflect/Object.h"

class A: public object_t {
public:
				A() = default;
				~A() = default;
				void show(){
								std::cout<< typeid(*this).name() << std::endl;
				}
public:
				std::string name_;
				std::vector<int> vecTest_;
};

REGISTER_CLASS(A);
REGISTER_FIELD(A, name_, string);
REGISTER_FIELD(A, vecTest_, std::vector<int>);
