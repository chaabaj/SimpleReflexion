#ifndef _REFLEXION_OBJECT_HPP_
#define _REFLEXION_OBJECT_HPP

#include "ClassInfo.hpp"
#include "PropertyContainer.hpp"
#include "MethodContainer.hpp"

namespace reflexion
{    
    template<typename T>
    class Object : public PropertyContainer, public MethodContainer
    {
    public:
        Object()
        {
        }
        ~Object()
        {
        }
        
        
        static ClassInfo<T> const &getClassInfo()
        {
            return s_classInfo;
        }
        
        template<typename ... Args>
        static std::shared_ptr<T>      construct(Args ... args)
        {
            return std::shared_ptr<T>(args...);
        }
        
    protected:
        static ClassInfo<T> const       s_classInfo;
    };
    
    template<typename T>
    const ClassInfo<T> Object<T>::s_classInfo = ClassInfo<T>();
}

#endif // _REFLEXION_OBJECT_HPP_