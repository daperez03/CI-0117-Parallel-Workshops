#ifndef THREAD_HPP
#define THREAD_HPP

#include <thread>

class Thread {
 protected:
  std::thread* thread = nullptr;

 public:
  Thread();
  virtual ~Thread();
  int startThread();
  int waitToFinish();

 protected:    
  virtual int run();
};

#endif