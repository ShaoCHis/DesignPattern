//
// Created by 少迟 on 2024/9/27.
//

#ifndef DESIGNPATTERN_BRIDGE_H
#define DESIGNPATTERN_BRIDGE_H
#include <iostream>


//桥接模式（Bridge Pattern）是一种结构型设计模式，它将抽象部分与其实现部分分离，使它们都可以独立变化。
//主要目的是将抽象层与实现层解耦，使得两者可以独立扩展互不影响
//与工厂模式不同的是，工厂模式负责创建对象实例，而桥接模式是为了将抽象与具体实现分离，达到解耦合的目的


/***
 * 角色定义：
 * - - Abstraction（抽象化角色）：定义抽象接口，维护一个对 Implementor 对象的引用
 * - - RefinedAbstraction（具体抽象化角色）：是 Abstraction 的一个子类，对 Abstraction 接口进行一些补充
 * - - Implementor（实现化角色）：定义实现化角色的接口，任何Abstraction角色可以调用
 * - - ConcreteImplementor（具体实现化角色）：Implementor 接口的具体实现
 */

/***
 * 工作原理：
 * - - 抽象化角色持有实现化角色的引用，它只需要定义与客户端的接口并委托给实现化角色来执行
 * - - 具体化角色继承抽象化角色并实现自己的业务逻辑，同时构造时关联相应的实现化角色
 */

/***
 * 优点：
 * - - 松耦合：抽象和实现两个部分可以独立的变化和发展，提高系统的可扩展性
 * - - 灵活性：由于抽象部分和实现部分被彻底分开，因此可以根据需要组合不同的抽象和实现，增强了系统的灵活性
 * - - 避免多重继承：如果采用传统的继承机制，可能会导致类层次过深或出现菱形继承问题，桥接模式可以避免
 */

//抽象类：指有纯虚函数的类

//桥接模式：实现系统可能有多个角度分类，（例如创建图形的形状与颜色），每一种分类都有可能变化，那么把这种多角度分离出来让他们独立变化

//例如：在该例子中
//Abstract可以看作图形的形状角度，通过RefinedAbstraction来定义形状的状态
//Implementor可以看作图形的颜色角度，通过ConcreteImplementor来实现图像颜色的变化
//例如有三个形状：A、B、C；三种颜色：a、b、c；对应组合为9种，就不需要创建9个子类来实现；几何级数的增长是我们不希望看到的
namespace BridgeMode{
    //实现化角色接口
    //定义了所有实现类共有的接口 operationImpl() ，它是抽象化角色依赖的具体操作
    //给出实现化角色的接口，但不给出具体的实现。实现化角色应当只给出底层操作，而抽象化角色应当给出更上一层的操作内容
    class Implementor{
    public:
        virtual ~Implementor(){}
        virtual void operationImpl() = 0;//定义操作接口
    };

    /***
     * 具体实现化角色（ConcreteImplementorA/B 分别提供了 operationImpl() 的不同实现
     */
    //具体实现化角色A
    class ConcreteImplementorA:public Implementor{
    public:
        void operationImpl() override{
            std::cout << "ConcreteImplementorA 的 operationImpl()\n";
        }
    };

    //具体实现化角色B
    class ConcreteImplementorB:public Implementor{
    public:
        void operationImpl() override{
            std::cout << "ConcreteImplementorB 的 operationImpl()\n";
        }
    };

    //抽象化角色
    //定义了抽象的操作 operation() ，但不提供具体实现。通过维持一个指向 Implementor 的指针来间接使用其实现
    //抽象化给出的定义，并保存一个对实现化对象的引用
    class Abstraction{
    protected:
        Implementor* _implementor;

    public:
        //构造函数接收一个 Implementor 对象的指针
        Abstraction(Implementor* impl) : _implementor(impl){}
        virtual ~Abstraction(){delete _implementor;}
        //定义抽象操作
        virtual void operation() = 0;
    };

    //具体抽象化角色
    //继承自 Abstraction ，在 operation() 中调用了 _implementor 的 operationImpl() 方法
    // ，这样就把具体实现细节交给了实现化角色
    //扩展抽象化角色，改正和修改对父类抽象化角色的操作和定义
    class RefinedAbstraction:public Abstraction{
    public:
        RefinedAbstraction(Implementor* impl): Abstraction(impl){}

        //实现抽象操作，调用 Implementor 的实现
        void operation() override{
            std::cout << "RefinedAbstraction 调用 operation...." << std::endl;
            _implementor->operationImpl();//委托实现化角色执行操作
        }
    };
}



//菱形继承与多重继承问题
namespace MultiInherit{
    //现在有类A和类B，两个类中均有 name 属性，那么使用类C继承A和B，则会存在访问 name 属性的二义性问题
    // ，需要额外添加 域运算符 来使用
    class A{
    protected:
        std::string name;
    };

    class B{
    protected:
        std::string name;
    };

    class C:public A,public B{
    public:
        void Print(){
            std::cout << MultiInherit::A::name << MultiInherit::B::name <<std::endl;
        }
    };


    //菱形继承
    //具有 类N 继承自 类P 和 类Q，同时类P和类Q均继承于类D，那么对于类N而言存在二义性问题，还会浪费存储空间
    class D{
    protected:
        std::string name;
    };

    class P:public D{
    public:
        void Print(){
            std::cout << name << std::endl;
        }
    };

    class Q:public D{
    public:
        void Print(){
            std::cout << name << std::endl;
        }
    };

    //通过内存分析得到 N 的内存占用为，含有两个 基类D ，分别保存有 P 和 Q 的数据
    //在 N 中进行属性访问需要额外添加域操作符来进行
    class N:public P,public Q{
    public:
        void Print(){
            std::cout << P::name << std::endl;
        }
    };
}

//TODO：为解决上述 多重继承以及菱形继承 的问题，C++引入虚基类概念-------——》在间接继承共同基类时只保留一份基类成员
//虚基类是在声明继承方式时指出，
// 类M 是 类A 的公共派生类，类A是类M的虚基类
//对于虚基类的初始化是由最后的派生类中负责初始化，在最后的派生类中不仅要对直接基类进行初始化，还要负责对虚基类初始化
namespace VirtualInherit{
    class A{
    public:
        A():_age(10),_name("ShaoCHi"){};

        A(std::uint32_t age,std::string name):_age(age),_name(std::move(name)){};
    protected:
        std::uint32_t _age;
        std::string _name;
    };

    class B:virtual public A{
    public:
        void Print(){
            std::cout << _name << _age << std::endl;
        }

        B() = default;

        B(std::uint32_t age,std::string name):A(age,std::move(name)){};
    };

    class C:virtual public A{
    public:
        void Print(){
            std::cout << _name << _age << std::endl;
        }

        C() = default;

        C(std::uint32_t age,std::string name):A(age,std::move(name)){};
    };
    //对于虚基类的初始化是由最后的派生类中负责初始化，在最后的派生类中不仅要对直接基类进行初始化，还要负责对虚基类初始化
    //C++编译器只执行最后的派生类对基类构造函数的调用，而忽略其他派生类对基类构造函数的调用，从而避免对基类成员数据进行重复初始化
    class D:public B,public C{
    public:
        //TODO:不用初始化基类🤔
        D():sex("male"){};

        //虚基类在派生类中仅仅存在一份，虚基类带有 virtual 关键字，在内存中也仅仅保留有一份，不会占用额外的内存空间
        //所以对基类中的属性访问可以直接利用属性名进行，不用再额外添加域运算符
        void Print(){
            std::cout << _age << _name << std::endl;
        }

    private:
        std::string sex;
    };
}

#endif //DESIGNPATTERN_BRIDGE_H
