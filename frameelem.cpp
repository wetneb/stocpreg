
#include "frameeelem.h"

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
	return mType.toString();
}


