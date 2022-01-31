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

- ![mymuduo框架](https://github.com/princeh23/mymuduo/blob/main/picture/mymuduo%E6%A1%86%E6%9E%B6.png)
- 
- MainReactor = baseloop_；SubReactor = subpool（如果没有定义subloop格式，IO和工作线程都是baseloop\_）
- ![并发模型](https://github.com/linyacool/WebServer/raw/master/datum/model.png)

# 压测

- webbench1.5

# TODO

- 









