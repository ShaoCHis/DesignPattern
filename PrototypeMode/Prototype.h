//
// Created by 少迟 on 2024/9/24.
//

#ifndef DESIGNPATTERN_PROTOTYPE_H
#define DESIGNPATTERN_PROTOTYPE_H
#include<iostream>
#include <utility>

//原型模式，Worker
/***
 * 原型模式可以在原有实例基础上快速复制一个同样的类型实例，然后根据需要可以进行属性的修改操作
 * 深拷贝开辟新的内存空间，复制一份原有实例的各项属性放入其中
 * 浅拷贝直接返回原有实例的内存地址进行操作
 *
 * 好处：
 * 在面对发生变化的情况下，克隆是最好的办法，这既隐藏了对象创建的细节，又对性能能是大大的提升
 * 可以完全忽略创建过程，仅仅考虑修改属性即可
 */
namespace PrototypeMode{
    class Prototype{
    public:
        virtual Prototype* CloneDeep() = 0;

        virtual Prototype* CloneShadow() = 0;

        virtual void Print() = 0;

        virtual ~Prototype()= default;
    };


    class Entity:public Prototype{
    public:
        Entity() =default;

        Entity(std::string name,std::uint32_t age):m_Name(std::move(name)),m_Age(age){}

        Entity(const Entity& entity){
            std::cout<<"copy"<<std::endl;
            this->m_Name = entity.m_Name;
            this->m_Age = entity.m_Age;
        }
        //深拷贝
        Entity* CloneDeep() override {
            return new Entity(*this);
        }

        //浅拷贝
        Entity* CloneShadow() override{
            return this;
        }

        void Print() override{
            std::cout << "name:"<<this->m_Name<<";"<<"age:"<<this->m_Age<<std::endl;
        }

        ~Entity() override {
            delete this;
        };

    private:
        std::string m_Name;
        std::uint32_t m_Age;
    };

    class Client{
    public:
        Client() = default;

        void Create(){
            Entity* clone_deep = entity->CloneDeep();
            std::cout << "parent address:" << entity << ";" <<
                      "clone deep son duplicates address:" << clone_deep << std::endl;
            Entity* clone_shadow = entity->CloneShadow();
            std::cout << "parent address:" << entity << ";" <<
                      "clone shadow son duplicates address:" << clone_shadow << std::endl;
        }
    private:
        Entity* entity = new Entity("ShaoCHi",23);
    };
}

#endif //DESIGNPATTERN_PROTOTYPE_H
