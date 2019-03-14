/*
 * @file Field.h
 *
 * Copyright 2019 . All rights reserved.
 * Use is subject to license terms.
 *
 * $Id$
 * $Date$
 */
#ifndef __simph_kern_Field_HPP__
#define __simph_kern_Field_HPP__
#include "Smp/IForcibleField.h"
#include "Smp/ISimpleField.h"
#include "simph/kern/Persist.hpp"
#include "simph/kern/Collection.hpp"
// workaround Smp headers issue.
namespace Smp {
class IDataflowField;
}
#include "Smp/IDataflowField.h"

namespace simph {
	namespace kern {

/**
 *
 */
class Field: public Persist, 
                    virtual public Smp::IDataflowField,
                    virtual public Smp::IForcibleField {
public:
    /**
     * Default constructor.
     */
    Field(Smp::String8 name, Smp::String8 description,
            Smp::ViewKind viewKind, void* address,
            unsigned int dataSize,
            Smp::Bool isState,
            Smp::Bool isInput,
            Smp::Bool isOutput,
            Smp::IObject* parent
            );
    /**
     * Destructor.
     */
    virtual ~Field();
    // Smp::IField implementation
    Smp::ViewKind GetView() const override;
    Smp::Bool IsState() const override;
    Smp::Bool IsInput() const override;
    Smp::Bool IsOutput() const override;
    const Smp::Publication::IType* GetType() const override;
    void Connect(Smp::IField* target) override;
    void Push() override;
    // Smp::IForcibleField implementation
    void Force(Smp::AnySimple value) override;
    void Unforce() override;
    Smp::Bool IsForced() override;
    void Freeze() override;

private:
    Smp::Bool _stateType;
    Smp::Bool _inputType;
    Smp::Bool _outputType;
    Smp::Publication::IType* _type;
    Smp::ViewKind _viewKind;
    void* _data;
    unsigned int _dataSize;
    Field* _src;
    Smp::Bool _forced;
    Smp::AnySimple _forcedValue;
    Collection<Field> _targets;
};

template <typename T>
class TField: virtual public Field {
public:
    TField(Smp::String8 name, Smp::String8 description,
            Smp::ViewKind viewKind, T* address,
            Smp::Bool isState,
            Smp::Bool isInput,
            Smp::Bool isOutput,
            Smp::IObject* parent
            ): 
                Field(name,description,viewKind,(void*) address,sizeof(T),
                        isState,isInput,isOutput,parent),
        _tData(address) {
    }
    virtual ~TField() {
    }
    // Smp::ISimpleField implementation
    Smp::AnySimple GetValue() const;

    void SetValue(Smp::AnySimple value) {
        *_tData=value;
    }

private:
    T* _tData;
};

}} // namespace simph::kern
#endif // __simph_kern_Field_HPP__
