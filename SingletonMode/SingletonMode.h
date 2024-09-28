//
// Created by 少迟 on 2024/9/24.
//

#ifndef DESIGNPATTERN_SINGLETONMODE_H
#define DESIGNPATTERN_SINGLETONMODE_H

/***
 * 单例模式，仅仅允许存在一个实例化对象
 */

class Singleton{
public:
    //删除拷贝构造函数，防止使用拷贝构造函数来进行对象属性的复制操作,Singleton singleton(Singleton::Get());
    Singleton(const Singleton&) = delete;

    static Singleton& Get() {
        static Singleton singleton;
        return singleton;
    }

    //将该方法作为静态方法进行调用，可以将调用更加转化为简单格式Singleton::Print();
    static void Print() {
        std::cout<<"Singleton Test\n" << Get().Random();
    }
private:
    Singleton(){};

    int m_Random;

    //TODO:切换为业务代码，单例模式一般用于全局数据共享，可以使用类属性来存有多种业务消息
    int Random() {
        m_Random = rand()%100;
        return m_Random;
    }
};


//类方法实现Singleton与命名空间区别为：
/***
 * 命名空间实现单例模式与类方法实现，在游戏引擎中，单例模式作为主控程序存在
 * 由于命名空间的特殊性，命名空间类似于函数调用，在调用时进行状态更新，本质上不存在实例
 */
namespace SingletonNamespace{
    int m_Random;
    int Random(){
        m_Random = rand()%100;
        return m_Random;
    };
}

#endif //DESIGNPATTERN_SINGLETONMODE_H
