# 文档

## 编译命令

cmake -B build -G "MinGW Makefiles"

cmake --build build --config Release --target install

[Link](https://github.com/Jia-Baos/Notes/blob/master/CMake/cmake-command.md)

## 同步与异步

同步：是指在不同进程之间的若干程序片断，它们的运行必须严格按照规定的某种先后次序来运行，这种先后次序依赖于要完成的特定的任务。如果用对资源的访问来定义的话，同步是指在互斥的基础上（大多数情况），通过其它机制实现访问者对资源的有序访问。在大多数情况下，同步已经实现了互斥，特别是所有写入资源的情况必定是互斥的。少数情况是指可以允许多个访问者同时访问资源。

互斥：是指散布在不同进程之间的若干程序片断，当某个进程运行其中一个程序片段时，其它进程就不能运行它们之中的任一程序片段，只能等到该进程运行完这个程序片段后才可以运行。如果用对资源的访问来定义的话，互斥某一资源同时只允许一个访问者对其进行访问，具有唯一性和排它性。但互斥无法限制访问者对资源的访问顺序，即访问是无序的。

## 线程间通信方式（提供线程间的同步支持）

1. 共享内存：

   - 线程可以通过读写共享内存区域来交换信息。这通常涉及到使用同步原语，如互斥锁（mutexes）、信号量（semaphores）、条件变量（condition variables）等，以确保数据的一致性和避免竞态条件。

2. 互斥锁（Mutex）：

   - 互斥锁用于保护共享资源，确保一次只有一个线程可以访问资源。当一个线程需要访问共享资源时，它会尝试锁定互斥锁。如果锁已被其他线程持有，它将等待直到锁可用。

3. 信号量（Semaphore）：

   - 信号量用于控制对共享资源的访问数量。它允许多个线程同时访问资源，但限制了同时访问的线程数量。信号量的值表示可用资源的数量。

4. 条件变量（Condition Variable）：

   - 条件变量用于线程间的同步，它允许线程在某些条件不满足时挂起，并在条件变为真时被唤醒。通常与互斥锁一起使用，以确保线程安全地检查条件并等待条件变化。

5. 事件（Event）：

   - 事件是一种同步机制，它允许一个线程通知其他线程某个特定的事件已经发生。线程可以等待事件被触发，一旦事件被设置，等待的线程就会被唤醒。

6. 读写锁（Read-Write Lock）：

   - 读写锁允许多个线程同时读取共享资源，但写入操作是互斥的。这意味着在任何时候，只有一个线程可以写入资源，而多个线程可以同时读取。

7. 信号量（Barrier）：

   - 信号量（或称为屏障）用于确保一组线程在继续执行之前都达到了某个点。这在需要多个线程协同工作的场景中非常有用。

8. 线程局部存储（Thread-Local Storage）：

   - 线程局部存储允许每个线程拥有自己的变量副本，这样每个线程可以独立地操作自己的数据，而不需要与其他线程共享。

9. 消息传递：

   - 线程可以通过消息队列或管道进行通信。一个线程发送消息，另一个线程接收消息。这种方法通常用于进程间通信，但也可以在线程间使用。

10. 原子操作：

    - 原子操作是不可分割的操作，它们在多线程环境中用于无锁编程。原子操作可以确保在执行过程中不会被其他线程中断，从而安全地更新共享数据。

| 工具 | 用途 | 特性 |
|-------|-------|-------|
| std::mutex | 保护共享资源免受并发访问 | 互斥 |
| std::condition_variable | 使线程在特定条件下等待 | 条件等待 |
| std::latch | 使线程在计数达到零时通过 | 一次性 |
| std::semaphore | 限制同时访问资源的线程数量 | 可重用 |
| std::barrier | 在某一点同步多个线程 | 自动重置 |
