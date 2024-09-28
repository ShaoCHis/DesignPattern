//
// Created by 少迟 on 2024/9/27.
//

#ifndef DESIGNPATTERN_BUILDER_H
#define DESIGNPATTERN_BUILDER_H

/***
 * 创建者模式
 * 在创建者模式下，利用虚函数的实际实现和继承来实现，
 * 统一流程的固定化与定制流程的定制操作
 *
 * 在BeefPizza下，进行CreatePizza()调用使用的基类的统一流程，但在PutMeat流程时，因为是BeefPizza重写了该方法，所以调用的定制化操作
 *
 * 不局限于单个流程的定制化，所有流程均可进行定制化操作
 */

#include <iostream>

namespace BuilderMode{
    class PizzaBuilder{
    public:
        PizzaBuilder() = default;

        void CreatePizza(){
            std::cout << "Creation Start\n";
            PutJam();
            PutMeat();
            PutVegetables();
            std::cout << "Creation End\n\n";
        }

    protected:
        static void PutJam(){
            std::cout << "Default Jam\n";
        }

        virtual void PutMeat(){
            std::cout << "Default Meat\n";
        }

        static void PutVegetables(){
            std::cout << "Default Vegetables\n";
        }
    };


    class BeefPizza:public PizzaBuilder{
    public:
        void PutMeat() override{
            std::cout << "Exchange TO Beef\n";
        }
    };


    class PorkPizza:public PizzaBuilder{
    public:
        void PutMeat() override{
            std::cout << "Exchange TO Pork\n";
        }
    };
}




#endif //DESIGNPATTERN_BUILDER_H
