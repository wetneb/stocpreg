#include "pregroup.h"

Pregroup* Pregroup::mGlobalPregroup = NULL;

Pregroup::Pregroup()
{

}

Pregroup::~Pregroup()
{

}

bool Pregroup::load(string filename)
{
    // TODO
}

bool Pregroup::loadPregroup(string filename)
{
    if(mGlobalPregroup == NULL)
    {
        mGlobalPregroup = new Pregroup();
        return mGlobalPregroup->load(filename);
    }

    return false;
}

void Pregroup::unloadPregroup()
{
    if(mGlobalPregroup != NULL)
        delete mGlobalPregroup;
}

bool Pregroup::strictlyLess(const string &lhs, const string &rhs)
{
    if(mGlobalPregroup)
    	return (lhs == rhs || (mGlobalPregroup->count(make_pair(lhs, rhs)) != 0));

    return lhs == rhs;
}

bool Pregroup::less(const string &lhs, const string &rhs)
{
    return (lhs == rhs || strictlyLess(lhs, rhs));
}

SimpleType::SimpleType(string baseType, int exponent) :
    exponent(exponent),
    baseType(baseType)
{
    ;
}

bool SimpleType::operator<=(const SimpleType &rhs) const
{
	return
    	(exponent == rhs.exponent && (
	 (exponent % 2 == 0 && Pregroup::less(baseType, rhs.baseType)) ||
	 (exponent % 2 == 1 && Pregroup::less(rhs.baseType, baseType))
	));	 
}

bool SimpleType::operator<(const SimpleType &rhs) const
{
	return
    	(exponent == rhs.exponent && (
	 (exponent % 2 == 0 && Pregroup::strictlyLess(baseType, rhs.baseType)) ||
	 (exponent % 2 == 1 && Pregroup::strictlyLess(rhs.baseType, baseType))
	));	 
}

bool SimpleType::gcon(const SimpleType &rhs) const
{
    return (exponent + 1 == rhs.exponent) && (*this <= rhs.leftAdjoint());
}

bool SimpleType::isUnit() const
{
    return baseType == "1";
}

SimpleType SimpleType::leftAdjoint() const
{
    SimpleType res(*this);
    res.exponent--;
    return res;
}

SimpleType SimpleType::rightAdjoint() const
{
    SimpleType res(*this);
    res.exponent++;
    return res;
}

string SimpleType::toString() const
{
    ostringstream out;
    out << baseType;

    if(exponent)
    {
        out << "(";
        char c = (exponent > 0 ? 'r' : 'l');
        int max = (exponent > 0 ? exponent : -exponent);
        for(int i = 0; i < max; i++)
            out << c;
        out << ")";
    }

    return out.str();
}

ComplexType::ComplexType()
{

}

ComplexType::ComplexType(SimpleType t)
{
    push_back(t);
}

string ComplexType::toString() const
{
    ostringstream out;

    for(ComplexType::const_iterator it = begin(); it != end(); it++)
        out << it->toString();

    return out.str();
}

// Adjoints
ComplexType ComplexType::leftAdjoint() const
{
    ComplexType result;
    for(ComplexType::const_reverse_iterator it = rbegin(); it != rend(); it++)
        result.push_back(it->leftAdjoint());
    return result;
}

ComplexType ComplexType::rightAdjoint() const
{
    ComplexType result;
    for(ComplexType::const_reverse_iterator it = rbegin(); it != rend(); it++)
        result.push_back(it->rightAdjoint());
    return result;
}

//! Defined only for data storage purposes
bool ComplexType::operator<(const ComplexType &rhs) const
{
    const std::list<SimpleType> *ptr = this, *rhs_p = &rhs;
    
    return (*ptr) < (*rhs_p);
}


