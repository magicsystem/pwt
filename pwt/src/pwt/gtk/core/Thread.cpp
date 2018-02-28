/*
 * Thread.cpp
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#include <pwt.h>

namespace pwt {

Mutex::Mutex() {
}

Mutex::~Mutex() {
}

int Mutex::create() {
}

bool Mutex::isOk() {
}

int Mutex::lock() {
}

int Mutex::unlock() {
}

MutexLocker::MutexLocker(Mutex& mutex) {
}

MutexLocker::~MutexLocker() {
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

