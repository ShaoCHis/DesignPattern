//
// Created by 少迟 on 2024/10/1.
//

#ifndef DESIGNPATTERN_FLYWEIGHT_H
#define DESIGNPATTERN_FLYWEIGHT_H

#include <iostream>
#include <map>
#include <memory>
#include <utility>

//享元模式是一种用于性能优化的设计模式，它通过共享对象来有效支持大量的细粒度对象以减少内存消耗。
// 这种模式适用于那些对象中大部分状态可以外部化，而只有少量内部状态（不随环境改变而改变的状态）的对象
namespace FlyweightMode {

    //抽象享元（Flyweight Interface）
    //定义了所有具体享元类共有的接口，通常包含内部状态和外部状态的操作方法。内部状态是可以共享的，而外部状态由客户端在每次调用时传入
    //定义了所有咖啡口味的基本行为，即服务（serve）咖啡
    class CoffeeFlavor {
    public:
        virtual ~CoffeeFlavor() {}

        //内部状态不变的操作
        virtual void serve(const std::string &extras, const std::string &size) const = 0;
    };

    //具体享元类
    //实现了咖啡口味的具体行为，并存储了口味名称这一内部状态
    class ConcreteCoffeeFlavor : public CoffeeFlavor {
    public:
        explicit ConcreteCoffeeFlavor(std::string flavorName) : _flavorName(std::move(flavorName)) {}

        void serve(const std::string &extras, const std::string &size) const override {
            std::cout << "Serving " << size << " cup of " <<
                      _flavorName << " with extras " << extras << std::endl;
        }

    private:
        std::string _flavorName;
    };

    //享元工厂
    //维护了一个储存所有咖啡口味实例的映射表，当客户请求某个口味的咖啡时，工厂会检查是否已经创建过该口味的实例，
    // 如果没有则创建一个新的实例，否则返回已有的实例，从而实现了口味的共享
    class CoffeeFlavorFactory {
    private:
        std::map<std::string, std::shared_ptr<CoffeeFlavor>> flavors;

    public:
        std::shared_ptr<CoffeeFlavor> getOrder(const std::string &flavor) {
            if (flavors.find(flavor) == flavors.end()) {
                //检查是否含有已经创建过实例，模版？
                flavors[flavor] = std::make_shared<ConcreteCoffeeFlavor>(flavor);
            }
            return flavors[flavor];
        }
    };

    class CoffeeOrder {
    private:
        std::shared_ptr<CoffeeFlavor> _flavor;
        std::string _extras;
        std::string _size;

    public:
        //外部传入的状态被装填进入，共享享元内部的信息（口味），由于外部状态的不同，每个订单都能得到个性化服务
        CoffeeOrder(std::shared_ptr<CoffeeFlavor> flavor, std::string extras, std::string size) : _flavor(
                std::move(flavor)), _extras(std::move(extras)), _size(std::move(size)) {}

        void serve() const {
            _flavor->serve(_extras, _size);
        }
    };
}


#endif //DESIGNPATTERN_FLYWEIGHT_H
