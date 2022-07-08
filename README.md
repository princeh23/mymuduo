# mymuduo介绍

- 从开源 C++ muduo 网络库，学习优秀的代码设计及其设计思想。 
- 基于事件驱动和事件回调的 epoll+线程池面向对象编程。 
-  基于 Multi-Reactor 架构以及 One Loop Per Thread 设计思想的多线程 C++网络库。 
- 重写 muduo 核心组件，去依赖 boost，用 C++11 重构，使用互斥锁以及智能指针管理对象。 
- 实现 Channel、Poller、EventLoop、TcpServer 等重要部分，学习 Buffer 缓冲区以及多线程异步日志的实现。 
# 环境配置

- ubuntu20.04虚拟机配置
- [win11 vscode链接虚拟机](https://www.cnblogs.com/hi3254014978/p/12681594.html)
- 安装cmake、g++

# mymuduo库的安装

- chmod +x autobuild.sh
- sudo ./autobuild.sh

# 测试

- example文件下
- sudo make
- ./testserver

# 项目架构Multi-Reactor
![mymuduo框架](https://github.com/princeh23/mymuduo/blob/main/picture/1.png)
![并发模型](https://github.com/linyacool/WebServer/raw/master/datum/model.png)

# 项目梳理/书写步骤
1. 第一模块：基本类
- noncopyable：不可拷贝的基类
- Logger：日志类
- Timestamp：时间类
- InetAddress：封装socket地址
2. 第二模块：Channel、Poller、EventLoop
- Channel：打包fd和感兴趣的events
- Poller：epoll、poll的基类
- EPollPoller：封装epoll的操作
- CurrentThread：获取当前线程tid，每个channel要在自己的eventloop线程上进行处理
- Eventloop：事件轮询，连接poller和channel
- Thread：底层线程
- EventLoopThread：one loop per thread，绑定一个loop和一个thread
- EventLoopThreadPoll：线程池，有mainloop和subloop
3. 第三模块：Acceptor、TcpServer、TcpConnection
- Socket：封装socker、bind、listen、accept
- Acceptor：处理accept，监听新用户的连接，打包成channel，分发给subloop
- TcpServer：集大成者，见图理解
- Buffer：缓冲区
- TcpConnection：建立和客户端的新连接
# 压测

- webbench1.5

# TODO
- 异步日志（AsyncLogging）
- epollpoller









