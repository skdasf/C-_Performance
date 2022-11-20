#pragma once

namespace djl
{
    namespace  utility
    {
        template<typename T>
        class singleton_t {
        public:
            static  T* getinstance()
            {
                static T* ins;
                if (ins == nullptr) {
                    ins = new T();
                }
                return ins;
             }
        private:
            singleton_t() = default;
            singleton_t(const singleton_t<T> &) = delete;
            singleton_t<T>& operator = (const singleton_t<T> &) = delete;
        };
    }


}