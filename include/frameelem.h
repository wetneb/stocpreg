
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
	    virtual string toString();
};

class LBElem : public FrameElem
{
    public:
	LBElem();
	bool isLB();
	string toString();
};

class RBElem : public FrameElem
{
    public:
	RBElem();
	bool isRB();
	string toString();
};

class StarElem : public FrameElem
{
    public:
	StarElem();
	bool isStar();
	string toString();
};

class TypeElem : public FrameElem
{
    public:
	TypeElem(SimpleType t);
	bool isType();
	string toString();

	SimpleType simpleType;
};

#endif

