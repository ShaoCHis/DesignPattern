//
// Created by 少迟 on 2024/9/27.
//

#ifndef DESIGNPATTERN_ADAPTER_H
#define DESIGNPATTERN_ADAPTER_H
#include "iostream"

namespace Adapter{
    //类适配器-------》缺点：多继承
    class Target{
    public:
        virtual void Request(){
            std::cout << "Target Request\n";
        }
    };

    //原有写好的接口，与当前系统的接口规范不兼容
    class Adaptee{
    public:
        void SpecialRequest(){
            std::cout << "Special Requests!\n";
        }
    };

    class Adapter:public Target,Adaptee{
    public:
        void Request() override{
            Adaptee::SpecialRequest();
        }
    };


    //类适配器,类适配器不存在多继承发生，程序的耦合度更低
    //同理，若该组建下
    class TargetClass{
    public:
        virtual void Request(){
            std::cout << "Target Request!\n";
        }
    };

    class AdapteeClass{
    public:
        void SpecialRequest(){
            std::cout << "SpecialRequest\n";
        }
    };

    class AdapterClass:public TargetClass{
    private:
        AdapteeClass* m_AdapteeClass;

    public:
        void Request() override{
            m_AdapteeClass->SpecialRequest();
        }

        ~AdapterClass(){
            delete m_AdapteeClass;
        }
    };

}


#endif //DESIGNPATTERN_ADAPTER_H
