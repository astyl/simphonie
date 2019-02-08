/*
 * @file Component.h
 *
 * Copyright 2019 . All rights reserved.
 * Use is subject to license terms.
 *
 * $Id$
 * $Date$
 */
#ifndef __simph_kern_Component_HPP__
#define __simph_kern_Component_HPP__
#include "simph/kern/Object.hpp"
#include "simph/kern/Collection.hpp"
#include "Smp/IComponent.h"

namespace simph {
	namespace kern {

/**
 *
 */
class Component: public Object, virtual public Smp::IComponent {
public:
    /**
     * Default constructor.
     */
    Component(Smp::String8 name,
                Smp::String8 descr="",
                Smp::IObject* parent=nullptr);
    /**
     * Destructor.
     */
    virtual ~Component();

    Smp::ComponentStateKind GetState() const;
    void Publish(Smp::IPublication* receiver);
    void Configure(Smp::Services::ILogger* logger);
    void Connect(Smp::ISimulator* simulator);
    Smp::IField* GetField(Smp::String8 fullName) const;
    const Smp::FieldCollection* GetFields() const;
    const Smp::Uuid& GetUuid() const;
protected:
    inline Smp::ISimulator* getSimulator() const {
        return _simulator;
    }
    virtual void publish(Smp::IPublication* receiver);
    virtual void configure();
    virtual void connect();
    inline void addField(Smp::IField* field) {
        _fields.push_back(field);
    }
    // TODO add log helpers ?
private:
    Smp::ComponentStateKind _state;
    Smp::Services::ILogger* _logger;
    Smp::ISimulator* _simulator;
    Collection<Smp::IField> _fields;
    Smp::Uuid _uuid;
};

}} // namespace simph::kern
#endif // __simph_kern_Component_HPP__
