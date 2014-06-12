#ifndef _REFLEXION_METHODCONTAINER_HPP_
#define _REFLEXION_METHODCONTAINER_HPP_

#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>
#include "Method.hpp"

namespace reflexion
{
    class MethodContainer
    {
    public:

        typedef std::unordered_map<std::string, std::shared_ptr<IMethod> >      ContainerType;

        MethodContainer();
        ~MethodContainer();


        template<typename ResultType = void, typename ... Args>
        ResultType call(std::string const &name, Args ... args)
        {
            IMethod     *method = this->getMethod(name);

            return (*static_cast<Method<ResultType (Args ... args)>* >(method))(args...);
        }

        template<typename ResultType = void, typename ... Args>
        ResultType call(std::string const &name, Args ... args) const
        {
            IMethod     *method = this->getMethod(name);

            return (*static_cast<Method<ResultType (Args ... args)>* >(method))(args...);
        }

        ContainerType const &getMethods() const;

        bool hasMethod(std::string const &name) const;

        unsigned int getArgumentLength(std::string const &name) const;

        void registerMethod(std::string const &name, std::shared_ptr<IMethod> method)
        {
            m_methods[name] = method;
        }
    private:

        IMethod const *getMethod(std::string const &name) const;

        IMethod *getMethod(std::string const &name);

    private:

        ContainerType   m_methods;
    };
}

#endif // _REFLEXION_METHODCONTAINER_HPP_