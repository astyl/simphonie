/*
 * @file Thread.h
 *
 * Copyright 2019 . All rights reserved.
 * Use is subject to license terms.
 *
 * $Id$
 * $Date$
 */
#ifndef __simph_sys_Thread_HPP__
#define __simph_sys_Thread_HPP__
#include <string>
#include <thread>
#include "simph/sys/Runnable.hpp"
namespace simph {
	namespace sys {

/**
 *
 */
class Thread {
public:
    /**
     * Default constructor.
     */
    Thread(std::string name, Runnable* toRun);
    /**
     * Destructor.
     */
    virtual ~Thread();

    inline void start();

    inline void run() {
        _running=true;
        _toRun->run();
        _running=false;
    }

    inline void join() {
        if (_running) {
            _th->join();
        }
    }
    
    inline std::string getName() {
        return _name;
    }

private:
    Runnable* _toRun;
    std::string _name;
    bool _running;
    std::thread* _th;
};

}} // namespace simph::sys
#endif // __simph_sys_Thread_HPP__
