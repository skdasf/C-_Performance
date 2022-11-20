#pragma once
#include <string>
#include "classFactory.h"
namespace djl {
    namespace reflect {
        class classRegister_t 
        {
        public:
            classRegister_t(const std::string &name, const  create_method& method)
            {
                auto factory = utility::singleton_t<classFactory_t>::getinstance();
                factory->register_class(name, method);
            }

            
            classRegister_t(const std::string& className, const std::string& fieldName, const std::string& t, size_t offset) {
               utility::singleton_t<classFactory_t>::getinstance()->register_field(className, fieldName, t, offset);
            }
        };


    }
}

#define  REGISTER_CLASS(className)                                             \
           	std::shared_ptr<object_t> createObject##className()                                        \
            {                                                                            \
                auto ptr = std::make_shared<className>();                                                                \
                ptr->setclassName(#className);                                                   \
                return ptr;                                                   \
            };                                                                               \
            djl::reflect::classRegister_t classRegister##className(#className, createObject##className);    \





#define  REGISTER_FIELD(className, fieldName, fieldType) \
            className className##fieldName; \
            djl::reflect::classRegister_t classRegister_t##className##fieldName(#className, #fieldName, #fieldType, ((size_t)&(className##fieldName.fieldName) -  (size_t)&(className##fieldName))); \

