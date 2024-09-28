//
// Created by 少迟 on 2024/9/24.
//

#ifndef DESIGNPATTERN_FATORYMODE_H
#define DESIGNPATTERN_FATORYMODE_H
#include <iostream>

//工厂模式
/***
 * 工厂模式将实际上的实例化对象模糊，在用户所接触的界面，用户仅仅需要告诉工厂需要什么类型的产品，然后工厂下发任务
 * 到具体的产品工厂进行实现
 * 面向用户是透明的
 *
 * 缺点：
 * 助长了Products的一致性，难以支持新品种
 *
 *
 * FactoryMethod只用考虑单一产品的创建与生成
 * AbstractFactory考虑一簇产品的创建与生成
 */

/****
 * 类中属性分类
 * public：不仅可以被该类及其派生类访问，还可以通过外部代码进行访问
 * protected：只能被该类及其派生类访问，不可以通过外部代码进行访问
 * private：只能被该类访问，不可以通过派生类和外部代码进行访问
 */


/***
 * 继承方式详解：
 * |----------------------------------------------------------------------------------|
 * |      类成员      |     public继承      |     protected继承    |     private继承     |
 * |----------------------------------------------------------------------------------|
 * |  基类的public成员 |  派生类的public成员  |  派生类的protected成员 |  派生类的private成员  |
 * |----------------------------------------------------------------------------------|
 * |基类的protected成员| 派生类的protected成员|  派生类的protected成员 |  派生类的private成员  |
 * |----------------------------------------------------------------------------------|
 * | 基类的private成员 |   在派生类中不可见    |     在派生类中不可见    |    在派生类中不可见   |
 * |----------------------------------------------------------------------------------|
 */

//抽象工厂的实现

namespace FactoryMode{
    //首先确定产品信息
    class Car{
    public:
        Car() = default;
        Car(std::string name,int index):m_Name(std::move(name)),m_Index(index){};

        virtual void show() = 0;

    protected:
        std::string m_Name;
        int m_Index;
    };

    class BMW: public Car{
    public:
        BMW() = default;
        //通过Car来构造BMW
        BMW(std::string name,int index):Car(std::move(name),index){};

        void show() override{
            std::cout << "Created " << m_Name << "; Index:" <<m_Index;
        }
    };

    class Audi:public Car{
    public:
        Audi() = default;
        //通过Car来构造
        Audi(std::string name,int index):Car(std::move(name),index){};

        void show() override{
            std::cout << "Created " << m_Name << "; Index:" <<m_Index;
        }
    };

    class Light{
    public:
        Light() = default;
        Light(std::string name):m_Name(std::move(name)){};

        virtual void show() = 0;

    protected:
        std::string m_Name;
    };

    class BMWLight:public Light{
    public:
        BMWLight(std::string name):Light(std::move(name)){};

        void show() override{
            std::cout << m_Name << " Light" << std::endl;
        }
    };

    class AudiLight:public Light{
    public:
        AudiLight(std::string name):Light(std::move(name)){};

        void show() override{
            std::cout << m_Name << " Light" << std::endl;
        }
    };



    class AbstractFactory{
    public:
        virtual Car* CreateCar(std::string name,int index) = 0;

        virtual Light* CreateLight(std::string name) = 0;


        virtual ~AbstractFactory() = default;
    };


    class AudiFactory:public AbstractFactory{
    public:
        Car* CreateCar(std::string name,int index) override{
            return new Audi(name,index);
        }

        Light* CreateLight(std::string name) override{
            return new AudiLight(name);
        }

        ~AudiFactory() override = default;
    };


    class BMWFactory:public AbstractFactory{
    public:
        Car* CreateCar(std::string name,int index) override{
            return new BMW(name,index);
        }

        Light* CreateLight(std::string name) override{
            return new BMWLight(name);
        }

        ~BMWFactory() override = default;
    };
}


#endif //DESIGNPATTERN_FATORYMODE_H
