#pragma once
#include "classFactory.h"

using namespace djl::reflect;

class object_t {
public:
    object_t() = default;
    virtual ~object_t() = default;

    template<typename T>
    void set_value(const std::string &name, const T& t);
    template<typename T>
    void get_value(const std::string &filedName, T& t);
    virtual void show() = 0;
    void setclassName(const std::string &name)
    {
        this->className = name;
    };
    const std::string& getClassName(){
        return className;
    }
    std::vector<std::string>  getallfield() {
        auto factory = djl::utility::singleton_t<djl::reflect::classFactory_t>::getinstance();
        return  factory->getAllFiledName(className);
    };
private:
    std::string className;
};

template<typename T>
void object_t::set_value(const std::string& name, const T& t) {
    auto factory = djl::utility::singleton_t<djl::reflect::classFactory_t>::getinstance();
    auto f = factory->get_field(className, name);
    auto offset = f.getoffset();
    *(T*)((unsigned char* )(this) +  offset) = t;
}

template<typename T>
void object_t::get_value(const std::string& filedName, T& t) {
    auto factory = djl::utility::singleton_t<djl::reflect::classFactory_t>::getinstance();
    auto f = factory->get_field(className, filedName);
    auto offset = f.getoffset();
    t = *(T*)((unsigned char*)(this) + offset);
}




