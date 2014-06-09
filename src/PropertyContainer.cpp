#include "PropertyContainer.hpp"

namespace reflexion
{
    PropertyContainer::PropertyContainer()
    {
    }
    
    PropertyContainer::~PropertyContainer()
    {
    }
    
    
    Mode PropertyContainer::getPropertyMode(std::string const &name) const
    {
        PropertyContainerType::const_iterator     it;
            
        if ((it = m_properties.find(name)) != m_properties.end())
        {
            return it->second->getMode();
        }
        throw std::runtime_error("Cannot retreive property");
    }
    
    bool PropertyContainer::hasProperty(std::string const &name) const
    {
        return m_properties.find(name) != m_properties.end();
    }
    
    PropertyContainer::PropertyContainerType const &PropertyContainer::getProperties() const
    {
        return m_properties;
    }
    
    IProperty const *PropertyContainer::retreiveProperty(std::string const &name, int mode) const
    {
        PropertyContainerType::const_iterator it;
        
        if ((it = m_properties.find(name)) != m_properties.end())
        {
            if (it->second->getMode() == mode)
            {
                return it->second.get();
            }
            else
            {
                throw std::logic_error("Invalid permission for property");
            }
        }
        throw std::runtime_error("Cannot retreive property");
    }
    
    IProperty *PropertyContainer::retreiveProperty(std::string const &name, int mode)
    {
        PropertyContainerType::iterator it;
        
        if ((it = m_properties.find(name)) != m_properties.end())
        {
            if (it->second->getMode() == mode)
            {
                return it->second.get();
            }
            else
            {
                throw std::logic_error("Invalid permission for property");
            }
        }
        throw std::runtime_error("Cannot retreive property");
    }
}