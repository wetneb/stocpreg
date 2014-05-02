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

SimpleType::SimpleType(string baseType, int exponent, string annotation) :
    exponent(exponent),
    baseType(baseType),
    annotation(annotation)
{
    ;
}


bool SimpleType::lessThan(const SimpleType &rhs) const
{
	return
    	(exponent == rhs.exponent && (
	 (exponent % 2 == 0 && Pregroup::less(fullType(), rhs.fullType())) ||
	 (exponent % 2 != 0 && Pregroup::less(rhs.fullType(), fullType()))
	));	 
}

bool SimpleType::strictlyLessThan(const SimpleType &rhs) const
{
	return
    	(exponent == rhs.exponent && (
	 (exponent % 2 == 0 && Pregroup::strictlyLess(fullType(), rhs.fullType())) ||
	 (exponent % 2 == 1 && Pregroup::strictlyLess(rhs.fullType(), fullType()))
	));	 
}

bool SimpleType::operator<(const SimpleType &rhs) const
{
    return (exponent < rhs.exponent || (exponent == rhs.exponent && fullType() < rhs.fullType()));
}

bool SimpleType::gcon(const SimpleType &rhs) const
{
    return (exponent + 1 == rhs.exponent) && (this->lessThan(rhs.leftAdjoint()));
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

string SimpleType::fullType() const
{
    ostringstream out;
    out << baseType;

    if(annotation != "")
        out << "[" << annotation << "]";
    return out.str();
}

string SimpleType::toString(bool annotation) const
{
    ostringstream out;
    out << (annotation ? fullType() : baseType);

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

bool SimpleType::fromString(const string &str)
{
    istringstream in(str);
    
    baseType = "";
    char c = '\0';
    in >> c;
    while(in.good() && c != '(' && c != '[')
    {
        baseType += c;
        in >> c;
    }

    if(c == '[')
    {
        while(in.good() && c != ']')
        {
            in >> c;
            annotation += c;
        }
    }
    
    exponent = 0;
    if(in.good())
    {
        in >> c;
        while(in.good() && (c == 'r' || c == 'l'))
        {
            exponent += (c == 'r' ? 1 : -1);
            in >> c;
        }
        return (c == ')');
    }
    else
        return true;
}

ComplexType::ComplexType()
{

}

ComplexType::ComplexType(SimpleType t)
{
    push_back(t);
}

string ComplexType::toString(bool annotation) const
{
    ostringstream out;

    for(ComplexType::const_iterator it = begin(); it != end(); it++)
    {
        if(it != begin())
            out << " ";
        out << it->toString(annotation);
    }

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

ComplexType ComplexType::operator*(const ComplexType& rhs) const
{
    ComplexType res(*this);
    ComplexType new_rhs(rhs);
    list<SimpleType>* right = (list<SimpleType>*)&new_rhs;
    res.splice(res.end(), *right);
    return res;
}

bool ComplexType::isUnit() const
{
    return (size() == 1 && begin()->isUnit());
}

//! Defined only for data storage purposes
bool ComplexType::operator<(const ComplexType &rhs) const
{
    const std::list<SimpleType> *ptr = this, *rhs_p = &rhs;
    
    return (*ptr) < (*rhs_p);
}

bool ComplexType::fromString(const string &str)
{
    istringstream in(str);

    clear();
    SimpleType st;
    while(in.good())
    {
        string tp;
        in >> tp;
        if(tp.size())
        {
            if(!st.fromString(tp))
            {
                cerr << "Error while parsing the simple type \""<<tp<<"\"" << endl;
                return false;
            }
            push_back(st);
        }
    }
    return true;
}

/*
bool ComplexType::operator==(const ComplexType &rhs) const
{
    const std::list<SimpleType> *ptr = this, *rhs_p = &rhs;

    return (*ptr) == (*rhs_p);
}
*/


