#include <iostream>
#include <memory>
#include "SingletonMode/SingletonMode.h"
#include "PrototypeMode//Prototype.h"
#include "FactoryMode/FatoryMode.h"
#include "BuilderMode/Builder.h"
#include "ProxyMode/Proxy.h"
#include "AdapterMode/Adapter.h"
#include "BridgeMode/Bridge.h"
#include "DecoratorMode/Decorator.h"
#include "FacadeMode/Facade.h"
#include "FlyweightMode/Flyweight.h"
#include "CompositeMode/Composite.h"
#include "TemplateMode/Template.h"
#include "StrategyMode/Strategy.h"
#include "CommandMode/Command.h"
#include <vector>

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

//装饰器模式
//通过装饰器模式，实际上面向用户的仍然是统一抽象接口，在抽象类的具体实现中改变基类的属性
void TestDecoratorMode(){
    std::unique_ptr<DecoratorMode::Base> decorator(new DecoratorMode::Decorator);
    decorator->Print();
}

//外观模式
//通过外观模式，将复杂的子系统调用配置为统一的接口为客户端服务
//子系统的更改对客户端完全透明，不影响客户端的任何使用
void TestFacadeMode(){
    std::unique_ptr<FacadeMode::Facade> facade(new FacadeMode::Facade);
    facade->method();
}

//享元模式
void TestFlyweightMode(){
    FlyweightMode::CoffeeFlavorFactory factory;

    //创建几个不同的订单，但是某些口味会被共享
    //在口味类别中，所有的口味是被共享的，shared_ptr，通过初始化传入外部信息创建订单内容
    std::vector<FlyweightMode::CoffeeOrder> orders = {
            {factory.getOrder("Espresso"),"no Sugar","small"},
            {factory.getOrder("Latte"),"extra foam","medium"},
            {factory.getOrder("Espresso"),"double Sugar","large"},
            {factory.getOrder("Cappuccino"),"cinnamon","medium"},
            {factory.getOrder("Espresso"),"single Sugar","small"}
    };

    for(const auto& order:orders){
        order.serve();
    }
}


//组合模式
//在树状结构的处理下，使用相同的处理方法对待根节点和叶子节点，上层无需考虑具体处理的对象是根节点还是叶子节点，
// 采用相同的接口进行处理，对上层透明
void PrintValue(CompositeMode::Entity* entity){
    std::cout << "该树状层次的价格为：" << entity->ComputeValue() << std::endl;
}

//继承子类传递时，如果有虚函数的重载，需要传递其指针编译器才能识别其重载函数的执行
/***
 * void PrintValue(CompositeMode::Entity entity)------->该entity传入将按照 entity 的 Compute 函数执行，value=0
 * void PrintValue(CompositeMode::Entity* entity) ----->该entity传入将按照 指针实际上的类型 Compute函数执行
 * 指针仅仅是指向一个地址，不考虑类型，类型为编译时解析
 * 同理，如果vector<Entity>为临时栈变量，传入时将进行  隐式类型转换为 Entity ，调用的函数为Entity Compute 函数
 * 在执行重载时，需要使用指针进行
 */
void TestCompositeMode(){
    CompositeMode::Product* product = new CompositeMode::Product();
    PrintValue(product);
    //创建 Box 树状层次结构;box--->(subBox,product1)
    //subBox--->(subProduct)
    CompositeMode::Box* box =  new CompositeMode::Box();
    std::vector<CompositeMode::Entity*> entities;
    CompositeMode::Product subProduct;
    CompositeMode::Box subBox;
    //均需传入地址，执行虚函数的重载函数执行
    entities.push_back(&subProduct);
    subBox.SetEntities(entities);
    CompositeMode::Product product1;
    std::vector<CompositeMode::Entity*> subEntities = {&subBox,&product1};
    box->SetEntities(subEntities);
    PrintValue(box);
}

//模版模式
//通过统一的接口来实现具体业务的不同实现方法
void TestTemplateMode(){
    std::unique_ptr<TemplateMode::Procession> procession(new TemplateMode::Business);
    procession->Process();
}

//策略模式
//动态更换调用的策略：例如游戏中针对不同角色，采用不同的攻击策略或者不同的角色信息
//unique_ptr需要显式调用类对象的构造函数，否则是空指针
void TestStrategyMode(){
    std::unique_ptr<StrategyMode::StrategyTest> strategyTest(new StrategyMode::StrategyTest());
    strategyTest->Set(StrategyMode::strategy::APC);
    strategyTest->Execution();
    strategyTest->Set(StrategyMode::strategy::ADC);
    strategyTest->Execution();
}

//  命令模式测试
//  通过对象的形式传入具体的命令交互，然后命令的执行并不需要判断命令的类型，降低系统的耦合度
//  增加和删除命令不会影响到其他类的变化，便于扩展
void TestCommandMode(){
    std::unique_ptr<CommandMode::Server> server(new CommandMode::Server());
    server->PushCommand(new CommandMode::AbstractCommand());
    server->PushCommand(new CommandMode::AddCommand());
    server->PushCommand(new CommandMode::SubCommand());
    server->Handle();
}

int main() {
    TestCommandMode();
    return 0;
}
