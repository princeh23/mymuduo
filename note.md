# mymuduo

### 一个典型的网络IO接口调用的两个阶段

- 数据准备
- 数据读写

### 阻塞、非阻塞

- 数据准备阶段

```c
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

- int size = recv(sockfd, buf, 1024, 0);
- 阻塞：数据没有到来时候阻塞在该函数
- 非阻塞：不阻塞，根据返回值进行判断

### 同步异步

- 数据读写阶段

int size = recv(sockfd, buf, 1024, 0);

- 数据在buf[]里面
- 同步：应用程序自己读取buf中的数据
- 异步：让操作系统去读取buf中的内容，约定通知方式，读取完毕后进行通知

### 阻塞/非阻塞与同步/异步关系

在处理IO的时候，阻塞和非阻塞都是同步IO，只有使用了特殊的API才是异步IO

### 5种IO模型

- 阻塞IO：等待数据准备，等待数据读写完再返回
- 非阻塞IO：一直轮询数据是否到来，到来之后进行数据读写
- IO多路复用：监听多个套接字，返回可读的fd，进行数据读写
- 信号驱动：数据准备好通知（第一阶段异步），读写还是应用程序来进行（第二阶段同步）
- 异步：约定好通知方式，内核进行等待数据到来、数据读写，全部做完通知应用程序

### 好的网络服务器设计

- one loop per thread is uaually a good model
- non-blocking + IO-multiplexing

### Recator模型

- 四个组件

### epoll

- select：数组，默认1024
- poll：链表，没有最大数量的限制
- epoll：红黑树（保存所有套接字），就绪链表（有事件发生的文件描述符）
- epoll_create()建立一个epoll对象
- epoll_ctl()向epoll对象种添加100w个套接字
- epoll_wait()在一段超时时间内等待一个fd上的时间，返回就绪的fd的个数
- fd：文件描述符

### LT、ET模式

- LT：内核数据没被读完，一直上报数据
- ET：内核数据只上报一次

### muduo用LT

- 不会丢失数据或者信息：应用没有读完
- 低延迟处理：每次读数据只要一次系统调用；公平，不会因为某个连接数据量过大影响其他处理连接消息
- 跨平台处理



### tcp_server编译启动

```shell
g++ -o server muduo_server.cpp -lmuduo_net -lmuduo_base -lpthread

./server
```

### vscode配置

- F1搜索C/C++ Edit configurations
- 可以在includePath加搜索路径 
- 增加新的语法标准 "cppStandard"："c++17"
- gcc -I头文件搜索路径 -L库文件搜索路径 -l库名称 /usr/include  /usr/local/inlclude*



- Ctrl+Shift+B 点齿轮可以添加依赖库，就不用命令行g++运行了



# 一些C++语法点

- 类外定义不加static、explict
- 定义、声明种默认参数只能出现一次
- 智能指针
- 需要派生类中的成员时候，不在基类中实现（eg：Poller中static Poller* newDefaultPoller(EventLoop *loop);）
- 默认值只能给一次，声明不能给
- (0) 不用 = 0；如果excplit？？？