#pragma once
#include <map>
#include <functional>
#include <string>
#include "../utility/singleton.h"
#include <memory>
#include <typeinfo>
#include <vector>
#include "classField.h"
class object_t;
typedef std::function<std::shared_ptr<object_t> ()> create_method;
namespace djl{
    namespace  reflect{
								class classFactory_t {
											friend class utility::singleton_t<classFactory_t>;
								public:
												void register_class(const std::string &class_name, const create_method& method);
												std::shared_ptr<object_t> create_class(const std::string &name);

												
												void register_field(const std::string &class_name, const std::string &fieldName, const std::string &t, size_t offset);
												int get_field_count(const std::string &name);
												classField_t get_field(const std::string &name, int pos);
												classField_t get_field(const std::string &name, const std::string &fieldName);
												std::vector<std::string> getAllFiledName(const std::string &className);
								private:
												classFactory_t() = default;
											 ~classFactory_t() = default;

								private:
												std::map<std::string, create_method> class_map_;				// 所有类的创建方法
												std::map<std::string, std::vector<classField_t>> class_field_;  // 所有类的字段
								};


    
    }


}