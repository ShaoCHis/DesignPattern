//
// Created by 少迟 on 2024/10/2.
//

#ifndef DESIGNPATTERN_COMPOSITE_H
#define DESIGNPATTERN_COMPOSITE_H
#include <iostream>
#include <utility>
#include <vector>

//应用的核心模型能用树状结构进行表示，在应用中使用组合模式才有价值
//组合模式使用一个通用接口来与树状结构的不同类型进行交互

//场景：有两类对象产品和盒子。一个盒子中可以包含多个产品或者几个较小的盒子，这些小盒子同样可以包含产品和一些更小的盒子
//组合模式使用一个通用的接口来与产品和盒子进行交互，然后在接口中声明一个计算总价的方法
//对于一个产品，该接口直接返回其价格
//对于一个盒子，该接口向下遍历直到计算出所有的价格后进行返回

//该模式最大的优点在于无需了解构成树状结构的对象的具体类，也无需了解对象是简单的产品还是复杂的盒子。
// 只需要调用通用接口以相同的方式对其进行处理即可


namespace CompositeMode{
    class Entity{
    public:
        virtual int ComputeValue(){
            return value;
        };
    protected:
        int value = 0;
    };

    class Product:public Entity{
    public:
        int ComputeValue() override{
            std::cout << "Compute Product value add 5\n";
            return value;
        }

    private:
        int value = 5;
    };

    class Box:public Entity{
    public:
        int ComputeValue() override{
            std::cout << "Compute Box value add 2\n";
            int sum = 0;
            sum+=value;
            for(Entity* entity:_entities){
                sum+=entity->ComputeValue();
            }
            return sum;
        }

        void SetEntities(std::vector<Entity*> entities){
            _entities = std::move(entities);
        }
    private:
        std::vector<Entity*> _entities;
        int value = 2;
    };
}

#endif //DESIGNPATTERN_COMPOSITE_H
