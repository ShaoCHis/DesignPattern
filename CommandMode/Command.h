//
// Created by 少迟 on 2024/10/10.
//

#ifndef DESIGNPATTERN_COMMAND_H
#define DESIGNPATTERN_COMMAND_H

/***
 * 命令模式：
 * 通过将具体的请求封装为具体的对象，使发出的请求责任与执行请求的责任分隔开，
 * 这样两者之间通过命令对象进行沟通，这样方便将命令对象进行存储、传递、调用、增加与管理
 *
 * 关键代码：定义三个角色，1、Command；2、Received真正的命令执行对象；3、invoker使用命令对象的入口
 */

//缺点：每增加一条命令需要增加一个命令类，会产生大量的具体命令类

#include <iostream>
#include <queue>
namespace CommandMode{
    //命令的实际执行者
    class HandlerCommand{
    public:
        void DefaultCommand() {
            std::cout << "Execute AbstractCommand Default\n";
        }

        void AddCommand() {
            std::cout << "Execute AbstractCommand Add\n";
        }

        void SubCommand() {
            std::cout << "Execute AbstractCommand Sub\n";
        }
    };


    //抽象命令类
    class AbstractCommand{
    public:
        virtual void Execute(){
            handlerCommand->DefaultCommand();
        }
        ~AbstractCommand(){
            delete handlerCommand;
        }

    protected:
        HandlerCommand* handlerCommand;

    };

    //具体命令类
    class AddCommand:public AbstractCommand{
    public:
        void Execute() override{
            handlerCommand->AddCommand();
        }
    };

    class SubCommand:public AbstractCommand{
    public:
        void Execute() override{
            handlerCommand->SubCommand();
        }
    };

    //命令的调用者
    class Server{
    public:
        //将命令压入队列中
        void PushCommand(AbstractCommand* abstractCommand){
            m_Commands.push(abstractCommand);
        }

        //队列执行命令，先进先出
        void Handle(){
            while(!m_Commands.empty()){
                m_Commands.front()->Execute();
                delete m_Commands.front();
                m_Commands.pop();
            }
        }
    private:
        std::queue<AbstractCommand*> m_Commands;
    };
}


#endif //DESIGNPATTERN_COMMAND_H
