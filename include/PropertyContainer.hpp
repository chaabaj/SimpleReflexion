#ifndef _REFLEXION_REFLEXIBLEPROPERTIES_HPP_
#define _REFLEXION_REFLEXIBLEPROPERTIES_HPP_

#include <string>
#include <memory>
#include <unordered_map>
#include "Property.hpp"

namespace reflexion
{
    class PropertyContainer
    {
    public:
        typedef std::unordered_map<std::string, std::shared_ptr<IProperty> >    PropertyContainerType;
        
        PropertyContainer();
        
        ~PropertyContainer();
        
        template<typename T, int mode = Read + Write>
        const typename get_type_info<T, Read>::LValueType getValue(std::string const &name) const
        {
            return (*static_cast<const Property<T, mode> *>(this->retreiveProperty(name, mode)));
        }
        
        template<typename T, int mode = Read + Write>
        void setValue(std::string const &name, typename get_type_info<T, mode>::RValueType value)
        {
            IProperty           *property = this->retreiveProperty(name, mode);
            Property<T, mode>   *prop;
            
            prop = static_cast<Property<T, mode> *>(property);
            *prop = value;
        }
        
        PropertyContainerType const &getProperties() const;
        
        Mode getPropertyMode(std::string const &name) const;
        
        bool hasProperty(std::string const &name) const;
        
        
        template<typename T, int mode = Read + Write>
        void registerProperty(std::string const &name, typename get_type_info<T, mode>::LValueType value)
        {
            std::shared_ptr<IProperty>  property(new Property<T, mode>(value));
            
            m_properties[name] = property;
        }
    private:
        
        IProperty const *retreiveProperty(std::string const &name, int mode) const;
        IProperty       *retreiveProperty(std::string const &name, int mode);
        IProperty       *retreiveProperty(std::string const &name);
        
    private:
        PropertyContainerType   m_properties;
    };
    
}

#endif // _REFLEXION_REFLEXIBLEOBJECT_HPP_