#include "Thread.h"
#include "CurrentThread.h"

#include <semaphore.h>

std::atomic_int Thread::numCreated_(0);//初始化

Thread::Thread(ThreadFunc func, const std::string &name)//构造函数
    : started_(false)
    , joined_(false)
    , tid_(0)
    , func_(std::move(func))
    , name_(name)
{
    setDefaultName();
}

Thread::~Thread()//析构函数
{
    if (started_ && !joined_)//线程已经运行起来并且不是工作线程join
    {
        thread_->detach();
		//thread类提供的设置分离线程的方法，成了1个守护线程，当主线程结束，守护线程自动结束
    }
}

void Thread::start()//一个Thread对象，记录的就是一个新线程的详细信息
{
    started_ = true;
    sem_t sem;
    sem_init(&sem, false, 0);

    //开启线程
    thread_ = std::shared_ptr<std::thread>(new std::thread([&](){
        //获取线程的tid值
        tid_ = CurrentThread::tid();
        sem_post(&sem);//加1操作
        //开启一个新线程，专门执行该线程函数
        func_();//包含一个eventloop
    }));//智能指针指向线程对象

    //这里必须等待获取上面新创建的线程的tid值
    sem_wait(&sem);//前面加1之后才能获取，才能解除阻塞
}

void Thread::join()
{
    joined_ = true;
    thread_->join();
}

void Thread::setDefaultName()//给线程设置默认的名字
{
    int num = ++numCreated_;
    if (name_.empty())//线程还没有名字
    {
        char buf[32] = {0};
        snprintf(buf, sizeof buf, "Thread%d", num);
        name_ = buf;
    }
}
