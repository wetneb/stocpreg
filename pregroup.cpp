#include "pregroup.h"


Pregroup::Pregroup()
{

}

bool Pregroup::less(const string &lhs, const string &rhs)
{
	return (lhs == rhs || (count(make_pair(lhs, rhs)) != 0));
}

SimpleType::SimpleType(string baseType, int exponent) :
    exponent(exponent),
    baseType(baseType)
{
    ;
}

bool SimpleType::operator<=(const SimpleType &rhs)
{
	return
    	(exponent == rhs.exponent && (
	 (exponent % 2 == 0 && mGlobalPregroup->less(*this, rhs)) ||
	 (exponent % 2 == 1 && mGlobalPregroup->less(rhs, *this))
	));	 
}

bool SimpleType::isUnit()
{
    return baseType == "1";
}

void SimpleType::serialize(Archive &ar, const unsigned int version)
{
	ar & baseType;
	ar & exponent;
}
