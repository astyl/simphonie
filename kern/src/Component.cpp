/*
 * @file Component.cpp
 *
 * Copyright 2019 . All rights reserved.
 * Use is subject to license terms.
 *
 * $Id$
 * $Date$
 */
#include "simph/kern/Component.hpp"
#include "simph/kern/InvalidComponentState.hpp"

namespace simph {
	namespace kern {
// --------------------------------------------------------------------
// ..........................................................
Component::Component() {
}
// ..........................................................
Component::~Component() {
}
// --------------------------------------------------------------------
// ..........................................................
Smp::ComponentStateKind Component::GetState() const {
    return _state;
}
// ..........................................................
void Component::Publish(Smp::IPublication* receiver) {
    if (_state!=Smp::ComponentStateKind::CSK_Created) {
        throw InvalidComponentState(_state,Smp::ComponentStateKind::CSK_Created);
    }
    publish(receiver);
    _state=Smp::ComponentStateKind::CSK_Publishing;
}
// ..........................................................
void Component::Configure(Smp::Services::ILogger* logger) {
    if (_state!=Smp::ComponentStateKind::CSK_Publishing) {
        throw InvalidComponentState(_state,Smp::ComponentStateKind::CSK_Publishing);
    }
    _logger=logger;
    configure();
    _state=Smp::ComponentStateKind::CSK_Configured;
}
// ..........................................................
void Component::Connect(Smp::ISimulator* simulator) {
    if (_state!=Smp::ComponentStateKind::CSK_Configured) {
        throw InvalidComponentState(_state,Smp::ComponentStateKind::CSK_Configured);
    }
    _simulator=simulator;
    connect();
    _state=Smp::ComponentStateKind::CSK_Connected;
}

}} // namespace simph::kern
