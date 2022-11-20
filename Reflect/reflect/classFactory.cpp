#include "classFactory.h"

namespace djl {
    namespace reflect {
        // 注册创建类的方法
        void classFactory_t::register_class(const std::string& class_name, const create_method& method)
        {
            if (class_map_.find(class_name) == class_map_.end()) {
                class_map_.insert(std::make_pair(class_name, method));
            }
        }

        // 生成类的实例对象
        std::shared_ptr<object_t> classFactory_t::create_class(const std::string& name)
        {
            auto it = class_map_.find(name);
            if (it == class_map_.cend()) {
               return nullptr;
            }
            return it->second();
        }

        void classFactory_t::register_field(const std::string& class_name, const std::string& fieldName, const std::string& t, size_t offset) {
            class_field_[class_name].push_back({ fieldName, t, offset });
        }

        int classFactory_t::get_field_count(const std::string& name)
        {
            return class_field_[name].size();
        }

        classField_t classFactory_t::get_field(const std::string& name, int pos)
        {
            auto size = class_field_[name].size();
            if (pos < 0 || pos >= size) {
                return {};
            }
            return  class_field_[name][pos];
        }

        classField_t classFactory_t::get_field(const std::string& name, const std::string& fieldName)
        {
            auto it = class_field_.find(name);
            if (it == class_field_.cend()) {
                return {};
            }
            for (const auto &iter : it->second) {
                if (iter.getfieldName() == fieldName) {
                    return iter;
                }
            }
            return {};
        }

        std::vector<std::string> classFactory_t::getAllFiledName(const std::string& className) {
            std::vector<std::string> res;
            auto it = class_field_.find(className);
            if (it == class_field_.cend()) {
                return {};
            }
            for (const auto &iter : it->second) {
                res.push_back(iter.getfieldName());
            }
            return res;
        }

    }
}

