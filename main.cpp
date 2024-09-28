#include <iostream>
#include <memory>
#include "SingletonMode/SingletonMode.h"
#include "PrototypeMode//Prototype.h"
#include "FactoryMode/FatoryMode.h"
#include "BuilderMode/Builder.h"
#include "ProxyMode/Proxy.h"
#include "AdapterMode/Adapter.h"
#include "BridgeMode/Bridge.h"

void TestSingletonMode() {
    Singleton::Print();
    //下述两种构建实例方法是不被允许的
    //Singleton singleton;
    //Singleton singleton1(Singleton::Get());
    std::cout << "命名空间：" << SingletonNamespace::Random() << std::endl;
}

void TestPrototypeMode() {
    PrototypeMode::Client client;
    //查看拷贝内存
    //深拷贝为创建一个新对象，浅拷贝返回原有对象地址
    client.Create();
}


//抽象工厂封装实际的产品工厂
//用户通过抽象工厂可以调用所有工厂的生产，然后通过工厂又具有具体的产品生产，提高代码的可扩展性
void TestFactorMode() {
    std::unique_ptr<FactoryMode::AbstractFactory> audiFactory(new FactoryMode::AudiFactory());
    std::unique_ptr<FactoryMode::AbstractFactory> bmwFactory(new FactoryMode::BMWFactory());

    audiFactory->CreateCar("audi A8", 8)->show();
    audiFactory->CreateLight("audi A6")->show();
    bmwFactory->CreateCar("BMW M3", 3)->show();
    bmwFactory->CreateLight("BMW M3 Light")->show();
}


//创建者模式
/***
 * 事物的完成需要一定的流程，相同的流程可以进行复用，特定的流程可以进行定制化更改
 */
void TestBuilderMode() {
    //默认构造
    BuilderMode::PizzaBuilder pizzaBuilder;
    pizzaBuilder.CreatePizza();

    //定制化构造
    BuilderMode::BeefPizza beefPizza;
    beefPizza.CreatePizza();

    BuilderMode::PorkPizza porkPizza;
    porkPizza.CreatePizza();
}

//代理模式
//Client 通过代理与终端获得链接
void TestProxyMode() {
    ProxyMode::Client client;
    client.ConnectionProxy("Iphone 14 pro", 8999);
}

//适配器模式通过Adapter来统一接口调用，满足业务需要
//在不改变原有基础的前提下，额外创造一个适配器类，来将原有的类适配到新的业务需要下
void TestAdapter() {
    std::unique_ptr<Adapter::Target> target(new Adapter::Adapter());
    target->Request();

    std::unique_ptr<Adapter::TargetClass> targetClass(new Adapter::AdapterClass());
    targetClass->Request();
}

//桥接模式
//可以根据需要为 Abstraction 实例化不同的 Implementor 对象，从而在运行时动态改变系统行为的目的
//通过这种方式，抽象与实现得以解耦，各自可以独立扩展而不影响对方
void TestBridgeMode() {
    std::unique_ptr<BridgeMode::Abstraction> absA(
            new BridgeMode::RefinedAbstraction(new BridgeMode::ConcreteImplementorA));
    absA->operation();

    std::unique_ptr<BridgeMode::Abstraction> absB(
            new BridgeMode::RefinedAbstraction(new BridgeMode::ConcreteImplementorB));
    absB->operation();

}

int main() {
    TestAdapter();
    return 0;
}
