//
// Created by 少迟 on 2024/10/1.
//

#ifndef DESIGNPATTERN_DECORATOR_H
#define DESIGNPATTERN_DECORATOR_H
#include <iostream>

//装饰器模式是在原有的基础上，添加额外的部分信息
//基类是确定的，通过装饰器来添加额外的装饰
//与BuilderMode不同的是，BuilderMode是确定的流程，然后流程中的某些步骤进行继承细化分成不同种类的结果
//装饰器模式是基类均相同，基类已经创建完成，在某些特殊的场景需要添加新的修饰物而产生

namespace DecoratorMode{
    class Base{
    public:
        virtual void Print(){
            std::cout << "color: " << _color << "; Length: " << _sizeLength
                    << "; Width: " << _sizeWidth << std::endl;
        }
    protected:
        enum{Green,Blue,Red,Yellow};
        std::uint32_t _color = Green;
        std::uint32_t _sizeLength = 3;
        std::uint32_t _sizeWidth = 4;
    };

    //通过装饰器额外为Base添加一个Logo
    class Decorator:public Base{
    public:
        void Print() override{
            std::cout <<"logo: " << _logo << "; color: " << _color << "; Length: " << _sizeLength
                      << "; Width: " << _sizeWidth << std::endl;
        }

    private:
        std::string _logo = "Audi";
    };
}

#endif //DESIGNPATTERN_DECORATOR_H
