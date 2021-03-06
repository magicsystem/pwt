/*
 * Thread.cpp
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */


#include <pwt.h>
#ifdef __linux
#include <pthread.h>

namespace pwt {
struct mutex_linux {
	pthread_mutex_t mutex;
	bool is_ok :1;
};

Mutex::Mutex() {
	create();
}

Mutex::~Mutex() {
	mutex_linux* m = (mutex_linux*) this->handles;
	if (m->is_ok) {
		pthread_mutex_destroy(&m->mutex);
	}
}

int Mutex::create() {
	mutex_linux* m = (mutex_linux*) this->handles;
	int err = pthread_mutex_init(&m->mutex, 0);
	if (err != 0) {
		m->is_ok = false;
		memset(&m->mutex, 0, sizeof(pthread_mutex_t));
	} else {
		m->is_ok = true;
	}
}

bool Mutex::isOk() {
	mutex_linux* m = (mutex_linux*) this->handles;
	return m->is_ok;
}

int Mutex::lock() {
	mutex_linux* m = (mutex_linux*) this->handles;
	int err = 0;
	if (m->is_ok) {
		err = pthread_mutex_lock(&m->mutex);
	}
	return err;
}

int Mutex::unlock() {
	mutex_linux* m = (mutex_linux*) this->handles;
	int err = 0;
	if (m->is_ok) {
		err = pthread_mutex_unlock(&m->mutex);
	}
	return err;
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

