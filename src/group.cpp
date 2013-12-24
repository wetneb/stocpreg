#include "group.h"

AbelianGroup* AbelianGroup::mGlobalAbelianGroup = NULL;

AbelianGroup::AbelianGroup()
{
    
}

AbelianGroup::~AbelianGroup()
{

}

bool AbelianGroup::load(string filename)
{
    // TODO
}

bool AbelianGroup::loadGroup(string filename)
{
    if(mGlobalAbelianGroup == NULL)
    {
        mGlobalAbelianGroup = new AbelianGroup();
        return mGlobalAbelianGroup->load(filename);
    }

    return false;
}

void AbelianGroup::unloadGroup()
{
    if(mGlobalAbelianGroup != NULL)
        delete mGlobalAbelianGroup;
}

bool AbelianGroup::strictlyLess(const string &lhs, const string &rhs)
{
    if(mGlobalAbelianGroup)
    	return (lhs == rhs || (mGlobalAbelianGroup->count(make_pair(lhs, rhs)) != 0));

    return lhs == rhs;
}

bool AbelianGroup::less(const string &lhs, const string &rhs)
{
    return (lhs == rhs || strictlyLess(lhs, rhs));
}

AbelianType::AbelianType()
{

}

AbelianType::AbelianType(string baseType, int exponent)
{
    if(baseType != "1" && exponent != 0)
        (*this)[baseType] = exponent;
}

string AbelianType::toString() const
{
    if(isUnit())
        return string("1");

    ostringstream out;

    for(AbelianType::const_iterator it = begin(); it != end(); it++)
        out << it->first << "(" << it->second << ") ";

    return out.str();
}

// Adjoints
AbelianType AbelianType::inverse() const
{
    AbelianType result;
    for(AbelianType::const_reverse_iterator it = rbegin(); it != rend(); it++)
        result[it->first] = - it->second;
    return result;
}

bool AbelianType::isUnit() const
{
    return (size() == 0);
}

// Group operation
AbelianType AbelianType::operator*(const AbelianType &rhs) const
{
    AbelianType res(*this);
    res *= rhs;
    return res;
}

AbelianType AbelianType::operator*=(const AbelianType &rhs)
{
    for(AbelianType::const_iterator it = rhs.begin();
            it != rhs.end(); it++)
    {
        int newExp = (*this)[it->first] + it->second;
        if(newExp)
            (*this)[it->first] += newExp;
        else
            this->erase(it->first);
    }
    return (*this);
}

//! Defined only for data storage purposes
bool AbelianType::operator<(const AbelianType &rhs) const
{
    const std::map<string, int> *ptr = this, *rhs_p = &rhs;
    
    return (*ptr) < (*rhs_p);
}

bool AbelianType::fromString(const string &str)
{
    istringstream in(str);

    clear();
    while(in.good())
    {
        string currentType;
        in >> currentType;
        istringstream curin(currentType);

        string baseType = "";
        char c = '\0';
        curin >> c;
        while(curin.good() && c != '(')
        {
            baseType += c;
            curin >> c;
        }

        int exponent = 0;
        if(curin.good())
        {
            curin >> exponent;
            if(!curin.good())
            {
                cerr<< "Error while parsing the group type \""<<currentType<<"\""<<endl;
                return false;
            }
            curin >> c;

            if(c != ')')
            {
                cerr << "Expecting '(' at the end of the group type \""<<currentType<<"\""<<endl;
                return false;
            }
        }

        if(baseType != "1")
            (*this)[baseType] = exponent;
    }
    return true;
}

