#include "MethodContainer.hpp"

namespace reflexion 
{
    MethodContainer::MethodContainer()
    {
    }
    
    MethodContainer::~MethodContainer()
    {
    }
    

    
    bool MethodContainer::hasMethod(std::string const &name) const
    {
        return m_methods.find(name) != m_methods.end();
    }
    
    unsigned int MethodContainer::getArgumentLength(std::string const &name) const
    {
        IMethod const *method = this->getMethod(name);
        
        return method->getArgumentLength();
    }
    
    IMethod *MethodContainer::getMethod(std::string const &name)
    {
        ContainerType::iterator it;
        
        if ((it = m_methods.find(name)) != m_methods.end())
        {
            return it->second.get();
        }
        throw std::runtime_error("Cannot get method");
    }
    
    IMethod const *MethodContainer::getMethod(std::string const &name) const
    {
        ContainerType::const_iterator it;
        
        if ((it = m_methods.find(name)) != m_methods.end())
        {
            return it->second.get();
        }
        throw std::runtime_error("Cannot get method");
    }
    
    MethodContainer::ContainerType const &MethodContainer::getMethods() const
    {
        return m_methods;
    }
}