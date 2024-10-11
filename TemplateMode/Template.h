//
// Created by 少迟 on 2024/10/4.
//

#ifndef DESIGNPATTERN_TEMPLATE_H
#define DESIGNPATTERN_TEMPLATE_H
#include <iostream>


//模版模式
//模版模式定义了算法的主要流程，但算法的具体骨干在 subclass 中实现，方便用户在自己的业务类中进行算法流程的具体实现
namespace TemplateMode{
    class Procession{
    public:
        void Process(){
            std::cout << "Process Start----------------\n";
            Algorithm();
            std::cout << "Process End------------------\n";
        }

    protected:
        virtual void Algorithm(){
            std::cout << "override Function for business in detail\n";
        }
    };

    class Business:public Procession{
    private:
        void Algorithm() override{
            std::cout << "This is Functional Business in detail for explicit business!\n";
        }
    };
}
#endif //DESIGNPATTERN_TEMPLATE_H
