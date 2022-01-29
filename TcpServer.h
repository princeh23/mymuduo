#pragma once

/**
 * 用户使用muduo编写服务器程序
 */ 
#include "EventLoop.h"
#include "Acceptor.h"
#include "InetAddress.h"
#include "noncopyable.h"
#include "EventLoopThreadPool.h"
#include "Callbacks.h"
#include "TcpConnection.h"
#include "Buffer.h"

#include <functional>
#include <string>
#include <memory>
#include <atomic>
#include <unordered_map>//哈希表 

//我们把需要用到的头文件都包含在这里，方便用户使用 
//对外的服务器编程使用的类
class TcpServer : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    enum Option//选项，是否对端口可重用 
    {
        kNoReusePort,
        kReusePort,
    };

    TcpServer(EventLoop *loop,
                const InetAddress &listenAddr,
                const std::string &nameArg,
                Option option = kNoReusePort);
    ~TcpServer();
    
    //用户在使用muduo库必须设置的 
    void setThreadInitcallback(const ThreadInitCallback &cb) { threadInitCallback_ = cb; }
    void setConnectionCallback(const ConnectionCallback &cb) { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback &cb) { messageCallback_ = cb; }
    void setWriteCompleteCallback(const WriteCompleteCallback &cb) { writeCompleteCallback_ = cb; }

    //设置底层subloop的个数
    void setThreadNum(int numThreads);

    //开启服务器监听 实际上就是开启mainloop的accptor的listen 
    void start();
private:
	//私有的内部使用的接口 
    void newConnection(int sockfd, const InetAddress &peerAddr);//有新连接来了 
    void removeConnection(const TcpConnectionPtr &conn);//有连接断开了，不要这条连接了 
    void removeConnectionInLoop(const TcpConnectionPtr &conn);

    using ConnectionMap = std::unordered_map<std::string, TcpConnectionPtr>;

    EventLoop *loop_;//baseLoop 用户定义的loop 一个线程一个loop循环 

    const std::string ipPort_;//服务器的IP地址端口号 
    const std::string name_;//服务器的名称 

    std::unique_ptr<Acceptor> acceptor_;//运行在mainLoop，任务就是监听新连接事件

    std::shared_ptr<EventLoopThreadPool> threadPool_;//线程池 one loop per thread

    ConnectionCallback connectionCallback_;//有新连接时的回调
    MessageCallback messageCallback_;//已连接用户有读写消息时的回调 reactor调用 
    WriteCompleteCallback writeCompleteCallback_;//消息发送完成以后的回调

    ThreadInitCallback threadInitCallback_;//loop线程初始化的回调

    std::atomic_int started_;//标志 

    int nextConnId_;
    ConnectionMap connections_;//保存所有的连接
};
