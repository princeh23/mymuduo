#pragma once
#include "noncopyable.h"

#include <functional>
#include <string>
#include <vector>
#include <memory>

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>; 

    EventLoopThreadPool(EventLoop *baseLoop, const std::string &nameArg);
    ~EventLoopThreadPool();

    void setThreadNum(int numThreads) { numThreads_ = numThreads; }//设置底层线程的数量 

    void start(const ThreadInitCallback &cb = ThreadInitCallback());//开启整个事件循环线程 

    //如果工作在多线程中，baseLoop_默认以轮询的方式分配channel给subloop
    EventLoop* getNextLoop();

    std::vector<EventLoop*> getAllLoops();//返回池里的所有loop 

    bool started() const { return started_; }
    const std::string name() const { return name_; }
private:

    EventLoop *baseLoop_;//最基本的loop,
	//对应一个线程，就是当前用户使用线程 EventLoop loop;负责用户的连接，已连接用户的读写 
	
    std::string name_;
    bool started_;
    int numThreads_;
    int next_;
    std::vector<std::unique_ptr<EventLoopThread>> threads_;//所有事件的线程 
    std::vector<EventLoop*> loops_;//事件线程的eventloop指针 
};
