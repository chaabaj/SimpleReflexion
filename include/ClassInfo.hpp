#ifndef _REFLEXION_CLASSINFO_HPP_
#define _REFLEXION_CLASSINFO_HPP_

#include <type_traits>

namespace reflexion
{
    
    template<typename T>
    class ClassInfo
    {
    public:
        ClassInfo()
        {
        }
        ~ClassInfo()
        {
        }
        
        bool isAbstract() const
        {
            return std::is_abstract<T>::value;
        }
        
        bool isPolymorphic() const
        {
            return std::is_polymorphic<T>::value;
        }
        
        template<typename U>
        bool operator==(ClassInfo<U> const &other) const
        {
            return std::is_same<T, U>::value;
        }
        
        
        template<typename U>
        bool operator!=(ClassInfo<U> const &other) const
        {
            return !ClassInfo<T>::operator==(other);
        }
        
    };
}

#endif