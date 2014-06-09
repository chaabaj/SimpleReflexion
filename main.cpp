#include <iostream>
#include <algorithm>
#include "Object.hpp"

using namespace reflexion;

struct Empty
{
};

typedef Object<Empty>   EmptyObject;

struct Test : public Object<Test>
{
public:
    
    Test()
    {
        m_a = 9;
        this->registerProperty<int>("m_a", m_a);
        this->registerProperty<float>("m_b", m_b);
        this->registerProperty<std::string>("m_name", m_name);
        this->registerMethod("print", make_method(&Test::print));
    }
    
    int print()
    {
        //std::cout << a << std::endl;
        std::cout << "lolololo" << std::endl;
        return 0;
    }
    
private:
    int m_a;
    float m_b;
    std::string m_name;
};

static void test()
{

}


int main(int argc, char** argv)
{
    MethodContainer::ContainerType::const_iterator      it;
    int a = 7;
    Test bla;
    EmptyObject newObj;
    
    EmptyObject::construct();
    newObj.registerProperty<int*>("m_a", &a);
    std::cout << *newObj.getValue<int*>("m_a") << std::endl;
    std::cout << (newObj.getClassInfo() == newObj.getClassInfo()) << std::endl;

    std::cout << bla.hasProperty("m_a") << std::endl;
    std::cout << bla.hasProperty("bka") << std::endl;
    bla.setValue<int>("m_a", 9);
    bla.setValue<std::string>("m_name", "blabla");
    std::cout << bla.getValue<std::string>("m_name") << std::endl;
    bla.call("print", &bla);
    a = bla.call<int>("print", &bla);
    std::cout << a << std::endl;
    std::cout << bla.getArgumentLength("print") << std::endl;
    std::cout << bla.hasMethod("toto") << std::endl;
    std::function<void()> fn = []()
    {
        std::cout << "TOTOTOTOOT" << std::endl;
    };
    bla.registerMethod("toto", make_method(fn));
    std::cout << bla.hasMethod("toto") << std::endl;
    bla.call("toto");
    bla.registerProperty<int>("m_toto", a);
    bla.setValue<int>("m_toto", 199);
    std::cout << bla.getValue<int>("m_toto") << std::endl;
    std::cout << bla.call<int>("print", &bla) << std::endl;
    
    std::cout << (newObj.getClassInfo() == bla.getClassInfo()) << std::endl;
    test();
}
