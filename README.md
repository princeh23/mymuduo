# mymuduo

- 一个基于reactor反应堆模型的多线程C++网络库
- 从开源C++ muduo网络库，学习优秀的代码设计
- 掌握基于事件驱动和事件回调的epoll+线程池面向对象编程
- 实现`TcpServer`、`TcpConnection`、`Poller`、`Chanel`等重要部分
- 重写muduo核心组件，去依赖boost，用C++11重构
- 测试代码是否成功
- ![并发模型](https://github.com/linyacool/WebServer/raw/master/datum/model.png)
- 
- ![img](https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2020/6/20/172d177f31e4e23d~tplv-t2oaga2asx-watermark.awebp)

# 环境配置

- ubuntu20虚拟机配置
- [win11 vscode链接虚拟机](https://www.cnblogs.com/hi3254014978/p/12681594.html)
- [boost库安装](https://blog.csdn.net/QIANGWEIYUAN/article/details/88792874)
- [muduo库安装](https://blog.csdn.net/QIANGWEIYUAN/article/details/89023980)





# 项目逻辑

​     — — — — — — — — — — — — — 

|         noncopyable ：不可拷贝的基类    |

|         Logger ：日志                                  |

|         TimeStamp                                      |

|         InetAddress                                     |

​    — — — — — — — — — — — — — 

- 一个线程有一个eventloop，一个eventloop有一个poller（poll、Epoll），一个poller可以监听多个channel（fd和事件的绑定），每个channel属于一个evenloop

- channel和poller是独立的，它们是不能直接互相通信的，它们都是依赖eventloop来通信的

​     — — — — —  — — — — —  — — — — — —  

| channel -> poller ->  EPollPoller ->  EventLoop   |

​     — — — — —  — — — — —  — — — — — —  

- EventLoop（one loop per thread）

  

- **Thread是底层的线程。
  EventloopThread是事件的线程
  EventloopThreadPool是事件循环线程池**
  
- Thread：一个线程

- EventLoopThread：绑定一个EventLoop和Thread，让EventLoopLoop运行在Thread上

- baseloop_：如果没有定义loop个数，IO和工作线程用的都是主线程（baseloop\_）

- mainReactor = baseloop_；subpool = subReactor

- EventLoopThreadPool：线程池，管理EventLoop



- loop相当于Reactor，poller相当于Demultiplex



- Acceptor fd来了打包成channel，唤醒subloop中



- TcpServer



- Socket：一个连接
- Callback、Buffer



- TcpConnection
- 





# mymuduo库的安装

- chmod +x autobuild.sh
- sudo ./autobuild.sh

# 测试

- example文件下
- sudo make
- ./testserver

