/*
 * @file DuplicateName.cpp
 *
 * Copyright 2019 . All rights reserved.
 * Use is subject to license terms.
 *
 * $Id$
 * $Date$
 */
#include "simph/kern/DuplicateName.hpp"
#include <sstream>

namespace simph {
	namespace kern {
// --------------------------------------------------------------------
// ..........................................................
DuplicateName::DuplicateName(Smp::IObject* sender, Smp::String8 dName) {
    _dName=dName;
    setName("DuplicateName");
    setSender(sender);
    std::ostringstream d;
    d << "Object named "<<_dName<<" already exists.";
    setDescription(d.str().c_str());
    setMessage();
}
// ..........................................................
DuplicateName::~DuplicateName() {
}
// --------------------------------------------------------------------
// ..........................................................
Smp::String8 DuplicateName::GetDuplicateName() const noexcept {
    return _dName.c_str();
}

}} // namespace simph::kern
