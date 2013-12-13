
#include "frameelem.h"

bool FrameElem::isLB()
{
    return false;
}

bool FrameElem::isRB()
{
    return false;
}

bool FrameElem::isStar()
{
    return false;
}

bool FrameElem::isType()
{
    return false;
}

LBElem::LBElem()
{
	;
}

bool LBElem::isLB()
{
	return true;
}

string LBElem::toString() const
{
	return "<";
}

FrameElem* LBElem::clone() const
{
    return (new LBElem(*this));
}


RBElem::RBElem()
{
	;
}

bool RBElem::isRB()
{
	return true;
}

string RBElem::toString() const
{
	return ">";
}

FrameElem* RBElem::clone() const
{
    return (new RBElem(*this));
}


StarElem::StarElem()
{
	;
}

bool StarElem::isStar()
{
	return true;
}

string StarElem::toString() const
{
	return "*";
}

FrameElem* StarElem::clone() const
{
    return (new StarElem(*this));
}


TypeElem::TypeElem(SimpleType t) :
    simpleType(t)
{
	;
}

bool TypeElem::isType()
{
	return true;
}

string TypeElem::toString() const
{
	return simpleType.toString();
}

FrameElem* TypeElem::clone() const
{
    return (new TypeElem(*this));
}


