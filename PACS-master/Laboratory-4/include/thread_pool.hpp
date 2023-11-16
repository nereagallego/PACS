#pragma once

#include <atomic>
#include <functional>
#include <vector>

#include<join_threads.hpp>
#include<threadsafe_queue.hpp>

#include <iostream>

class thread_pool
{
  std::atomic<bool> _done;
  size_t _num_threads;
  threadsafe_queue<std::function<void()>> _work_queue;
  std::vector<std::thread> _threads;
  join_threads _joiner;

  using task_type = void();

  void worker_thread()
  {
     while(!_done)
     {
        std::function<void()> task;
        if (_work_queue.try_pop(task))
        {
            task(); // Execute the task
        } else {
            std::this_thread::yield(); // Avoid busy-waiting
        }
     }
  }

  public:
  thread_pool(size_t num_threads = std::thread::hardware_concurrency())
    : _done(false), _num_threads(num_threads), _work_queue(), _joiner(_threads)
  {
    try
    {
      for(size_t i = 0; i < _num_threads; ++i)
      {
        _threads.push_back(std::thread(&thread_pool::worker_thread, this));
      }
    }
    catch(...)
    {
      _done = true;
      throw;
    }
  }

  ~thread_pool()
  {
    wait();
    _done = true;
  }

  void wait()
  {
      // wait for completion
      while(!_work_queue.empty())
      {
          // active waiting
          std::this_thread::yield();
      }
  }

  template<typename F>
    void submit(F f)
    {
      _work_queue.push(std::function<task_type>(f));
    }
};
