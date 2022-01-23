#pragma once

#include "noncopyable.h"
#include "Timestamp.h"

#include <functional>
#include <memory>

class EventLoop;
class Timestamp;


/**
 * Channel 理解为通道，封装了sockfd和其感兴趣的event，如EPOLLIN、EPOLLOUT事件
 * 还绑定了poller返回的具体事件
 */
class Channel: noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop *loop, int fd);
    ~Channel();

    void handleEvent(Timestamp receiveTime);


private:
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;   //事件循环
    const int fd_;      //fd，Poller监听的对象
    int events_;        //注册fd感兴趣的事件
    int revents_;       //poller返回地具体发生的事件
    int intdex_;        

    std::weak_ptr<void> tie_;
    bool tied_;

    //因为channel通道里面能够获知fd最终发生的具体事件revents,所以它负责调用具体事件的回调操作
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};