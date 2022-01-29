#pragma once

#include <vector>
#include <string>
#include <algorithm>

//网络库底层的缓冲器类型定义
class Buffer
{
public:
    static const size_t kCheapPrepend = 8;//头部字节大小 记录数据包的长度 
    static const size_t kInitialSize = 1024;//缓冲区的大小 

    explicit Buffer(size_t initialSize = kInitialSize)
        : buffer_(kCheapPrepend + initialSize)//开辟的大小 
        , readerIndex_(kCheapPrepend)
        , writerIndex_(kCheapPrepend)
    {}

    size_t readableBytes() const //可读的数据长度 
    {
        return writerIndex_ - readerIndex_;
    }

    size_t writableBytes() const //可写的缓冲区长度 
    {
        return buffer_.size() - writerIndex_;
    }

    size_t prependableBytes() const //返回头部的空间的大小 
    {
        return readerIndex_;
    }

    //返回缓冲区中可读数据的起始地址
    const char* peek() const
    {
        return begin() + readerIndex_;
    }

    //在onMessage的时候 把数据从Buffer转成string类型 
    void retrieve(size_t len)
    {
        if (len < readableBytes())
        {
            readerIndex_ += len;//应用只读取了刻度缓冲区数据的一部分，就是len，还剩下readerIndex_ += len -> writerIndex_
        }
        else//len == readableBytes()
        {
            retrieveAll();
        }
    }

    void retrieveAll()
    {
        readerIndex_ = writerIndex_ = kCheapPrepend;
    }

    //把onMessage函数上报的Buffer数据，转成string类型的数据返回
    std::string retrieveAllAsString()
    {
        return retrieveAsString(readableBytes());//应用可读取数据的长度
    }

    std::string retrieveAsString(size_t len)
    {
        std::string result(peek(), len);
        retrieve(len);//上面一句把缓冲区中可读的数据，已经读取出来，这里肯定要对缓冲区进行复位操作
        return result;
    }

    //buffer_.size() - writerIndex_    写len长的数据 
    void ensureWriteableBytes(size_t len)
    {
        if (writableBytes() < len)
        {
            makeSpace(len);//扩容函数
        }
    }

    //把[data, data+len]内存上的数据，添加到writable缓冲区当中
    void append(const char *data, size_t len)
    {
        ensureWriteableBytes(len);
        std::copy(data, data+len, beginWrite());
        writerIndex_ += len;
    }

    char* beginWrite()
    {
        return begin() + writerIndex_;
    }

    const char* beginWrite() const
    {
        return begin() + writerIndex_;
    }

    //从fd上读取数据
    ssize_t readFd(int fd, int* saveErrno);
    //通过fd发送数据
    ssize_t writeFd(int fd, int* saveErrno);
private:
    char* begin()
    {
        //it.operator*() 获取迭代器指向的内容，然后取个地址 
        return &*buffer_.begin();//vector底层数组首元素的地址，也就是数组的起始地址
    }
    const char* begin() const
    {
        return &*buffer_.begin();
    }
    void makeSpace(size_t len)
    {
        if (writableBytes() + prependableBytes() < len + kCheapPrepend)
        {
            buffer_.resize(writerIndex_ + len);
        }
        else
        {
            size_t readalbe = readableBytes();
            std::copy(begin() + readerIndex_, //未读取的数据往前搬 
                    begin() + writerIndex_,
                    begin() + kCheapPrepend);
            readerIndex_ = kCheapPrepend;//回到原位置  8下标位置 
            writerIndex_ = readerIndex_ + readalbe;
        }
    }

    std::vector<char> buffer_;//vector数组 扩容方便 
    size_t readerIndex_;//可读数据的下标位置 
    size_t writerIndex_;//写数据的下标位置 
};
