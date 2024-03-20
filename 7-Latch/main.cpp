/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief 闩（latch）和屏障（barrier）
 * @version 0.1
 * @date 2024-03-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <functional>
#include <iostream>
#include <latch>
#include <string>
#include <thread>

struct Job {
  const std::string name;
  std::string product{"未工作"};
  std::thread acton{};
};

int main(int argc, char *argv[]) {
  Job jobs[]{{"Annika"}, {"Buru"}, {"Chuck"}};

  std::latch work_done{std::size(jobs)};
  std::latch start_clean_up{1};

  auto work = [&](Job &my_job) {
    my_job.product = my_job.name + " 已工作";
    work_done.count_down();
    start_clean_up.wait();
    my_job.product = my_job.name + " 已清理";
  };

  std::cout << "工作启动... ";
  for (auto &job : jobs) {
    job.acton = std::thread{work, std::ref(job)};
  }

  work_done.wait();
  std::cout << "完成：" << std::endl;
  for (auto &job : jobs) {
    std::cout << "  " << job.product << std::endl;
  }

  std::cout << "清理工作线程... ";
  start_clean_up.count_down();
  for (auto &job : jobs) {
    job.acton.join();
  }

  std::cout << "完成：" << std::endl;
  for (auto &job : jobs) {
    std::cout << "  " << job.product << std::endl;
  }
}
