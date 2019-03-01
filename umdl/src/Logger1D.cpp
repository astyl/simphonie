/*
 * @file Logger1D.cpp
 *
 * Copyright 2019 . All rights reserved.
 * Use is subject to license terms.
 *
 * $Id$
 * $Date$
 */
#include "simph/umdl/Logger1D.hpp"
#include "Smp/IPublication.h"
#include <sstream>

namespace simph {
	namespace umdl {
// --------------------------------------------------------------------
// ..........................................................
Logger1D::Logger1D(Smp::String8 name, Smp::String8 descr,
                                           Smp::IObject* parent):
                        Component(name,descr,parent),
                        AStepMdl(name,descr,parent) {
}
// ..........................................................
Logger1D::~Logger1D() {
}
// --------------------------------------------------------------------
// ..........................................................
void Logger1D::publish(Smp::IPublication* receiver) {
    receiver->PublishField("in","Input: value to log",&_in,
            Smp::ViewKind::VK_All,false,true,false);
}
// ..........................................................
void Logger1D::step() {
    std::ostringstream s;
    s<<_in;
    logInfo(s.str().c_str());
}

}} // namespace simph::umdl
