/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 通过条件变量进行线程间的通信，cond.notify_one()
 * @version 0.1
 * @date 2024-03-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mu;                // 互斥锁全局变量
std::condition_variable cond; // 全局条件变量
std::deque<int> q;            // 双端队列标准容器全局变量

// 生产者，往队列放入数据
void function_1()
{
    int count = 10;
    while (count > 0)
    {
        std::unique_lock<std::mutex> locker(mu);
        q.push_front(count); // 数据入队锁保护
        locker.unlock();

        cond.notify_one(); // 向一个等待线程发出“条件已满足”的通知

        std::this_thread::sleep_for(std::chrono::seconds(1)); // 延时1秒
        count--;
    }
}
// 消费者，从队列提取数据
void function_2()
{
    int data = 0;
    while (data != 1)
    {
        std::unique_lock<std::mutex> locker(mu);

        // 判断队列是否为空
        while (q.empty())
        {
            // 解锁互斥量并陷入休眠以等待通知被唤醒，被唤醒后加锁以保护共享数据
            cond.wait(locker);
        }

        data = q.back();
        q.pop_back(); // 数据出队锁保护
        locker.unlock();
        std::cout << "t2 got a value from t1: " << data << std::endl;
    }
}

int main()
{
    std::thread t1(function_1);
    std::thread t2(function_2);
    t1.join();
    t2.join();
    return 0;
}