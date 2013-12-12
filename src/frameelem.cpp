
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

string FrameElem::toString()
{
    return "";
}

LBElem::LBElem()
{
	;
}

bool LBElem::isLB()
{
	return true;
}

string LBElem::toString()
{
	return "<";
}


RBElem::RBElem()
{
	;
}

bool RBElem::isRB()
{
	return true;
}

string RBElem::toString()
{
	return ">";
}


StarElem::StarElem()
{
	;
}

bool StarElem::isStar()
{
	return true;
}

string StarElem::toString()
{
	return "*";
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

string TypeElem::toString()
{
	return simpleType.toString();
}


