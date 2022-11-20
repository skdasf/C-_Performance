#pragma once
#include <string>
namespace djl {
    namespace reflect {
								class classField_t {
								public:
												~classField_t() = default;
												classField_t():field_type_(""), field_name_(""), offset_(0){}
												classField_t(const std::string &fieldName, const std::string & fieldType,
																								 size_t offset):field_type_(fieldType), field_name_(fieldName), offset_(offset){}

												std::string getfieldName()const{ return field_name_;}
												std::string getfieldType()const{ return field_type_;}
												size_t getoffset() const { return offset_;};
								private:
												std::string field_name_;
												std::string field_type_;
												size_t offset_;

								};    
    }


}