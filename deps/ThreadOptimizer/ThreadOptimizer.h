#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <sys/syscall.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

class ThreadOptimizer
{
private:
	void Routine();

	std::mutex m_Mutex;
	std::vector<pid_t> m_Threads;
public:
	ThreadOptimizer();
	~ThreadOptimizer();

	void PushThread(pid_t tid);
};

