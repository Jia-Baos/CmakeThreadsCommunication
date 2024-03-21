/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 原子变量示例
 * @version 0.1
 * @date 2024-03-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <atomic>
#include <thread>

std::atomic_flag flag = ATOMIC_FLAG_INIT;

void func(int id) {
  while (flag.test_and_set(std::memory_order_acquire)) {
    // 等待其他线程释放锁
  }

  std::cout << "Thread " << id << " acquired the lock." << std::endl;

  // 模拟业务处理
  std::this_thread::sleep_for(std::chrono::seconds(1));

  flag.clear(std::memory_order_release);  // 释放锁
  std::cout << "Thread " << id << " released the lock." << std::endl;
}

int main(int argc, char* argv[]) {
  std::thread t1(func, 1);
  std::thread t2(func, 2);

  t1.join();
  t2.join();

  return 0;
}