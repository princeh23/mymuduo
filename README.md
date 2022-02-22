# mymuduo介绍

- 一个基于reactor反应堆模型的多线程C++网络库
- 从开源C++ muduo网络库，学习优秀的代码设计
- 掌握基于事件驱动和事件回调的epoll+线程池面向对象编程
- 实现`TcpServer`、`TcpConnection`、`Poller`、`Chanel`等重要部分
- 重写muduo核心组件，去依赖boost，用C++11重构
- 测试代码是否成功

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

# 项目架构
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









