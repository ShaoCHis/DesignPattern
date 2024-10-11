//
// Created by 少迟 on 2024/10/4.
//

#ifndef DESIGNPATTERN_STRATEGY_H
#define DESIGNPATTERN_STRATEGY_H
#include <iostream>


//策略模式可以在运行过程中动态选择执行的策略，不用停止程序进行切换
//在策略模式中，通过策略的选择进行动态执行
namespace StrategyMode{
    typedef enum {
        DEFAULT,ADC,APC,SUP
    }strategy;

    //通过策略进行选择具体执行策略
    class Strategy{
    public:
        Strategy(strategy strategy):_strategy(strategy){};
        Strategy() = default;

        virtual void Solution(){
            std::cout << "Default Solution Strategy!\n" << "Strategy："<<_strategy;
        }

    protected:
        strategy _strategy = DEFAULT;
    };

    class StrategyADC:public Strategy{
    public:
        StrategyADC(strategy one):Strategy(one){};

        void Solution() override{
            std::cout << "Override Solution StrategyADC!\n" << "Strategy："<<_strategy;
        }
    };

    class StrategyAPC:public Strategy{
    public:
        StrategyAPC(strategy two):Strategy(two){};

        void Solution() override{
            std::cout << "Override Solution StrategyAPC!\n" << "Strategy："<<_strategy<<std::endl;
        }
    };

    class StrategySUP:public Strategy{
    public:
        StrategySUP(strategy three):Strategy(three){};

        void Solution() override{
            std::cout << "Override Solution StrategySUP!\n" << "Strategy："<<_strategy<<std::endl;
        }
    };

    //通过策略测试提供统一入口进行策略的跳转使用
    class StrategyTest{
    public:
        ~StrategyTest(){
            delete _strategy;
        }
        void Set(strategy type){
            delete _strategy;
            switch (type) {
                case strategy::ADC:
                    _strategy = new StrategyADC(type);
                    break;
                case strategy::APC:
                    _strategy = new StrategyAPC(type);
                    break;
                case strategy::SUP:
                    _strategy = new StrategySUP(type);
                    break;
                default:
                    break;
            }
        }

        void Execution(){
            this->_strategy->Solution();
        }

    private:
        Strategy* _strategy = new Strategy(strategy::DEFAULT);
    };
}


#endif //DESIGNPATTERN_STRATEGY_H
