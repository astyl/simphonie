/*
 * @file DLib.h
 *
 * Copyright 2019 . All rights reserved.
 * Use is subject to license terms.
 *
 * $Id$
 * $Date$
 */
#ifndef __simph_sys_DLib_HPP__
#define __simph_sys_DLib_HPP__
#ifdef WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include <string>

namespace simph {
	namespace sys {

/**
 *
 */
class DLib {
public:
    /**
     * Default constructor.
     */
    DLib(const char* libName);
    /**
     * Destructor.
     */
    virtual ~DLib();

    template<typename FT>
    FT getEntry(const char* symbol) {
#ifdef WIN32
        return reinterpret_cast<FT>(GetProcAddress(_lib,symbol));
#else
        return reinterpret_cast<FT>(dlsym(_lib,symbol));
#endif
        // TODO throw exception on error.
    }
    inline std::string getName() {
        return _name;
    }
private:
#ifdef WIN32
    HMODULE _lib;
#else
    void* _lib;
#endif
    std::string _name;
};

}} // namespace simph::sys
#endif // __simph_sys_DLib_HPP__
