//
// Created by 少迟 on 2024/9/27.
//

#ifndef DESIGNPATTERN_BRIDGE_H
#define DESIGNPATTERN_BRIDGE_H
#include <iostream>


//桥接模式（Bridge Pattern）是一种结构型设计模式，它将抽象部分与其实现部分分离，使它们都可以独立变化。
//主要目的是将抽象层与实现层解耦，使得两者可以独立扩展互不影响

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

//TODO:菱形继承问题，虚继承解决

//抽象类：指有纯虚函数的类

//桥接模式：实现系统可能有多个角度分类，（例如创建图形的形状与颜色），每一种分类都有可能变化，那么把这种多角度分离出来让他们独立变化

//例如：在该例子中
//Abstract可以看作图形的形状角度，通过RefinedAbstraction来定义形状的状态
//Implementor可以看作图形的颜色角度，通过ConcreteImplementor来实现图像颜色的变化
//例如有三个形状：A、B、C；三种颜色：a、b、c；对应组合为9种，就不需要创建9个子类来实现；几何级数的增长是我们不希望看到的
namespace BridgeMode{
    //实现化角色接口
    //定义了所有实现类共有的接口 operationImpl() ，它是抽象化角色依赖的具体操作
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

#endif //DESIGNPATTERN_BRIDGE_H
