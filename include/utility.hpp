#ifndef _REFLEXION_UTILITY_HPP_
#define _REFLEXION_UTILITY_HPP_

#include <type_traits>
#include <functional>

namespace reflexion
{
    enum Mode
    {
        Read = 1,
        Write = 2
    };
    
    struct NullType
    {
    };
    
    template<typename T, typename U>
    struct associate : public T, public U
    {
        template<typename ... Args>
        associate(Args& ... args) : T(args...), U(args...)
        {
        }
        
        ~associate()
        {
        }

    };
    
    template<typename T, int mode>
    struct get_type_info;
    
    template<typename T>
    struct get_type_info<T, Read>
    {
    private:
        typedef get_type_info<T, Write>                                         TypeInfo;
    public:
        typedef typename std::add_const<typename TypeInfo::RValueType>::type    RValueType;
        
        typedef typename std::add_const<typename TypeInfo::LValueType>::type    LValueType;
        
    };
    
    template<typename T>
    struct get_type_info<T, Write>
    {
        typedef typename std::conditional<std::is_pointer<T>::value, NullType, 
                                          typename std::add_rvalue_reference<T>::type>::type    RValueType;
                                          
        typedef typename std::conditional<std::is_pointer<T>::value, T, 
                                          typename std::add_lvalue_reference<T>::type>::type    LValueType;
    };
    
    template<typename T>
    struct get_type_info<T, Read + Write>
    {
        typedef typename get_type_info<T, Write>::RValueType    RValueType;
        typedef typename get_type_info<T, Write>::LValueType    LValueType;
    };
    
    template<typename T> 
    struct count_arg;
    
    template<typename R, typename ...Args> 
    struct count_arg<R(Args...) >
    {
        static const std::size_t value = sizeof...(Args);
    };
    
}

#endif // _REFLEXION_UTILITY_HPP_