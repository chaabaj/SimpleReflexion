#ifndef _REFLEXION_PROPERTY_HPP_
#define _REFLEXION_PROPERTY_HPP_

#include <memory>
#include <type_traits>
#include "utility.hpp"

namespace reflexion
{
    
    class IProperty
    {
    public:
        virtual ~IProperty() {}
        
        virtual Mode getMode() const = 0;
    };
    
    template<typename T>
    class WritePolicy
    {
    public:
        typedef typename get_type_info<T, Write>::LValueType    LValueType;
        typedef typename get_type_info<T, Write>::RValueType    RValueType;
        
        WritePolicy(LValueType value) : _value(value)
        {
        }
        
        virtual ~WritePolicy()
        {
        }
        
        void set(const LValueType newValue)
        {
            _value = newValue;
        }
        
        void set(const RValueType newValue)
        {
            _value = newValue;
        }
        
    private:
        LValueType    _value;
    };
    
    template<typename T>
    class ReadPolicy
    {
    public:
        typedef typename get_type_info<T, Read>::LValueType    LValueType;
        
        ReadPolicy(LValueType value) : _value(value)
        {
        }
       
        virtual ~ReadPolicy()
        {
        }
        
        LValueType get() const
        {
            return _value;
        }
        
    private:
        LValueType      _value;
    };
    

    template<class T, int mode = Read + Write>
    class Property : public IProperty
    {
        typedef typename std::conditional<mode == Read, ReadPolicy<T>, WritePolicy<T> >::type   TmpStoragePolicy;
    public:
        typedef typename std::conditional<mode == Read + Write, associate< ReadPolicy<T>, 
                                          WritePolicy<T> >, TmpStoragePolicy >::type            StoragePolicy;
                                          
        typedef typename get_type_info<T, mode>::LValueType                                     LValueType;
        typedef typename get_type_info<T, mode>::RValueType                                     RValueType;
         
        Property(LValueType value) : _storage(value)
        {
        }
        
        ~Property()
        {
        }
        
        Mode getMode() const
        {
            return static_cast<Mode>(mode);
        }
        
        void operator()(const RValueType v)
        {
            _storage.set(v);
        }
        
        void operator()(const LValueType v)
        {
            _storage.set(v);
        }
        
        Property &operator=(const RValueType newValue)
        {
            _storage.set(newValue);
        }
        
        Property &operator=(const LValueType newValue)
        {
            _storage.set(newValue);
        }
        
        operator const LValueType() const
        {
            return _storage.get();
        }
        
    private:

        
    private:
        StoragePolicy   _storage;
    };
    
    template<typename T>
    using ReadOnlyProperty = Property<T, Read>;
    
    template<typename T>
    using WriteOnlyProperty = Property<T, Write>;
    
    
}

#endif // _REFLEXION_PROPERTY_HPP_