# mymuduo

- 一个基于reactor反应堆模型的多线程C++网络库
- ubuntu20虚拟机配置
- [win11 vscode链接虚拟机](https://www.cnblogs.com/hi3254014978/p/12681594.html)
- [boost库安装](https://blog.csdn.net/QIANGWEIYUAN/article/details/88792874)
- [muduo库安装](https://blog.csdn.net/QIANGWEIYUAN/article/details/89023980)





- 项目逻辑

​     — — — — — — — — — — — — — 

|         noncopyable ：不可拷贝的基类    |

|         Logger ：日志                                  |

|         TimeStamp                                      |

|         InetAddress                                     |

​    — — — — — — — — — — — — — 

一个线程有一个eventloop，一个eventloop有一个poller（poll、Epoll），一个poller可以监听多个channel（fd和事件的绑定），每个channel属于一个evenloop

​     — — — — — 

| channel -> poller ->  EPollPoller ->    |

​    — — — — — 
