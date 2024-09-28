//
// Created by 少迟 on 2024/9/27.
//

#ifndef DESIGNPATTERN_PROXY_H
#define DESIGNPATTERN_PROXY_H
#include <iostream>
#include <utility>
//代理者模式Proxy
/***
 * 提供给Client的接口不能直接给，需要找到一个代理中介
 * 例如：
 * 网购，商家与客户之间不能直接进行交易，需要通过物流公司来进行交易
 * 客户只需要收物流公司的快件，不用考虑快件的本质来源（可以做到无痛更换商家而保持对上层透明）
 */


namespace ProxyMode{
    class Target{
    private:
        std::string _name = "Default";
        std::uint32_t _price = 0;
    protected:
        void ExchangeState(std::string name,uint32_t price){
            std::cout << _name << ":" << _price << std::endl;
            this->_name = std::move(name);
            this->_price = price;
            std::cout << "Exchange!" << _name << ":" << _price << std::endl;
        }
    };

    class Proxy:public Target{
    public:
        Proxy() = default;
        //提供外部接口进行实际连接，封装实际目标的函数调用
        void ConnectionTarget(std::string name,std::uint32_t price){
            ExchangeState(std::move(name),price);
        }
    };

    class Client{
    public:
        void ConnectionProxy(std::string name,std::uint32_t price){
            //获取代理，通过代理调用目标函数
            Proxy proxy;
            proxy.ConnectionTarget(std::move(name),price);
        }
    };
}


#endif //DESIGNPATTERN_PROXY_H
