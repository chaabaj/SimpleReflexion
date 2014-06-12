#ifndef _REFLEXION_METHOD_HPP_
#define _REFLEXION_METHOD_HPP_

#include <memory>
#include <stdexcept>
#include "utility.hpp"

namespace reflexion
{
    class IMethod
    {
    public:
        virtual ~IMethod() {}

        virtual unsigned int getArgumentLength() const = 0;
    };

    template<typename Signature>
    class Method : public IMethod
    {
    public:
        typedef std::function<Signature>                                FunctionType;
        typedef Signature                                               SignatureType;
        typedef typename std::function<SignatureType>::result_type      ReturnType;

        Method(std::function<Signature> &callable) : m_callable(callable)
        {
        }

        ~Method()
        {
        }

        template<typename ... Args>
        ReturnType operator()(Args ... args)
        {
            if (!m_callable)
            {
                throw std::runtime_error("Callable object is null");
            }
            if (count_arg<ReturnType (Args...)>::value != this->getArgumentLength())
            {
                throw std::logic_error("Number of arguments is incorrect");
            }
            return m_callable(args...);
        }

        template<typename ... Args>
        ReturnType operator()(Args ... args) const
        {
            if (!m_callable)
            {
                throw std::runtime_error("Callable object is null");
            }
            if (count_arg<ReturnType (Args...)>::value != this->getArgumentLength())
            {
                throw std::logic_error("Number of arguments is incorrect");
            }
            return m_callable(args...);
        }

        unsigned int getArgumentLength() const
        {
            return count_arg<Signature>::value;
        }

    private:
        std::function<Signature>        m_callable;
    };

    template<typename ObjectClass, typename ResultType, typename ... Args>
    std::shared_ptr<Method<ResultType (ObjectClass*, Args...)> > make_method(ResultType (ObjectClass::*method)(Args...))
    {
        typedef ResultType (Signature)(ObjectClass*, Args...);

        std::function<Signature> fn = method;
        return std::shared_ptr<Method<Signature> >(new Method<Signature>(fn));
    }

    template<typename ResultType, typename ... Args>
    std::shared_ptr<Method<ResultType (Args...)> > make_method(std::function<ResultType (Args...)> method)
    {
        typedef ResultType (Signature)(Args...);

        return std::shared_ptr<Method<Signature> >(new Method<Signature>(method));
    }
}

#endif // _REFLEXION_METHOD_HPP_