
#ifndef INCLUDED_FRAMEELEM_H
#define INCLUDED_FRAMEELEM_H

#include "pregroup.h"

class FrameElem
{
	public:
	    virtual bool isLB();
	    virtual bool isRB();
	    virtual bool isStar();
	    virtual bool isType();
	    virtual string toString() const = 0;
        virtual FrameElem* clone() const = 0;
};

class LBElem : public FrameElem
{
    public:
        LBElem();
        bool isLB();
        string toString() const;
        FrameElem* clone() const;
};

class RBElem : public FrameElem
{
    public:
        RBElem();
        bool isRB();
        string toString() const;
        FrameElem* clone() const;
};

class StarElem : public FrameElem
{
    public:
        StarElem();
        bool isStar();
        string toString() const;
        FrameElem* clone() const;
};

class TypeElem : public FrameElem
{
    public:
        TypeElem(SimpleType t);
        bool isType();
        string toString() const;
        FrameElem* clone() const;

        SimpleType simpleType;
};

#endif

