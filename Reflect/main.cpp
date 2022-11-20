#include <iostream>
#include "./reflect/classFactory.h"
#include "A.h"
#include "B.h"
using namespace djl;

int main()
{
    auto factory = utility::singleton_t<reflect::classFactory_t>::getinstance();
    auto a = factory->create_class("A");
    a->show();
    std::string name("djl");
    a->set_value("name_", name);
    std::string str;
    a->get_value("name_", str);
    std::cout<<str;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    auto res = a->getallfield();
    auto b = factory->create_class("B");
    b->show();
    utility::singleton_t<reflect::classFactory_t>::getinstance();


    return 0;
}