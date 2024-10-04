//
// Created by 少迟 on 2024/10/1.
//

#ifndef DESIGNPATTERN_FACADE_H
#define DESIGNPATTERN_FACADE_H
#include<iostream>

namespace FacadeMode{
    class SubSystem_1{
    public:
        void Print(){
            std::cout << "SubSystem_1 call\n";
        }
    };

    class SubSystem_2{
    public:
        void Print(){
            std::cout << "SubSystem_2 call\n";
        }
    };

    class SubSystem_3{
    public:
        void Print(){
            std::cout << "SubSystem_3 call\n";
        }
    };


    //由 Facade 统一调用子系统的对上层提供的功能，对上层透明子系统的实现
    //为多个复杂的子系统调用提供一个统一的上层接口，降低子系统和客户端之间的耦合度，使得子系统变化不会影响调用他的客户端
    //对客户屏蔽了子系统
    class Facade{
    public:
        //对上层调用的统一接口
        void method(){
            system1.Print();
            system2.Print();
            system3.Print();
        }

    private:
        SubSystem_1 system1;
        SubSystem_2 system2;
        SubSystem_3 system3;
    };
}


#endif //DESIGNPATTERN_FACADE_H
