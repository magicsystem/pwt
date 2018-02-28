/*
 * Thread.h
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_CORE_THREAD_H_
#define INCLUDE_PWT_CORE_THREAD_H_
#include "Object.h"
namespace pwt {

class PUBLIC Mutex: public PlatformObject {
private:
	void* handles[11];
public:
	Mutex();
	~Mutex();
	int create();
	bool isOk();
	int lock();
	int unlock();
};

class PUBLIC MutexLocker {
private:
	Mutex* mutex;
public:
	MutexLocker(Mutex& mutex);
	~MutexLocker();
};

class PUBLIC Thread: public PlatformObject {
public:
	Thread();
	~Thread();
	enum State {
		NEW, RUNNABLE, BLOCKED, WAITING, TIMED_WAITING, TERMINATED
	};
public:
	static Thread* currentThread();
	static void yield();
	static void sleep(int millis);
	void start();
	void run();
	void exit();
	void stop();
	void interrupt();
	bool isInterrupted();
	bool isAlive();
	void suspend();
	void resume();
	void setPriority(int newPriority);
	int getPriority();
	int activeCount();
	void join(int millis);
	void join();
	int getId();
	State getState();
};

} /* namespace pwt */

#endif /* INCLUDE_PWT_CORE_THREAD_H_ */
