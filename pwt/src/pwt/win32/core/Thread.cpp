/*
 * Thread.cpp
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#include <pwt.h>
#ifdef __WIN
#include <windows.h>

namespace pwt {
struct mutex_windows {
	CRITICAL_SECTION mutex;
	//bool is_ok :1;
};

Mutex::Mutex() {
	mutex_windows* m = (mutex_windows*) this->handles;
	memset(m, 0, sizeof(mutex_windows));
	create();
}

Mutex::~Mutex() {
	mutex_windows* m = (mutex_windows*) this->handles;
	//if (m->is_ok) {
	DeleteCriticalSection(&m->mutex);
	//}
}

int Mutex::create() {
	mutex_windows* m = (mutex_windows*) this->handles;
	InitializeCriticalSection(&m->mutex);
	//m->is_ok = true;
	return 1;
}

bool Mutex::isOk() {
	return true;
}

int Mutex::lock() {
	mutex_windows* m = (mutex_windows*) this->handles;
	//if (m->is_ok) {
	EnterCriticalSection(&m->mutex);
	//}
	return 1;
}

int Mutex::unlock() {
	mutex_windows* m = (mutex_windows*) this->handles;
	//int err = 0;
	//if (m->is_ok) {
	LeaveCriticalSection(&m->mutex);
	//}
	return 1;
}

MutexLocker::MutexLocker(Mutex& mutex) {
	this->mutex = &mutex;
	mutex.lock();
}

MutexLocker::~MutexLocker() {
	this->mutex->unlock();
}

Thread::Thread() {
}

Thread::~Thread() {
}

Thread* Thread::currentThread() {
}

void Thread::yield() {
}

void Thread::sleep(int millis) {
}

void Thread::start() {
}

void Thread::run() {
}

void Thread::exit() {
}

void Thread::stop() {
}

void Thread::interrupt() {
}

bool Thread::isInterrupted() {
}

bool Thread::isAlive() {
}

void Thread::suspend() {
}

void Thread::resume() {
}

void Thread::setPriority(int newPriority) {
}

int Thread::getPriority() {
}

int Thread::activeCount() {
}

void Thread::join(int millis) {
}

void Thread::join() {
}

int Thread::getId() {
}

Thread::State Thread::getState() {
}

} /* namespace pwt */
#endif

