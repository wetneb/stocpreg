
#ifndef INCLUDED_PREGROUP_H
#define INCLUDED_PREGROUP_H

class Pregroup : public std::set<std::pair<string,string> >
{
	public:
	    Pregroup();


};

class SimpleType
{
    public:
	SimpleType(Pregroup &p, string baseType, int exponent);

	bool operator<=(const SimpleType &rhs) const;

    private:
	int mExp;
	string mBaseType;
	Pregroup &mPregroup;
};

class ComplexType : public std::list<SimpleType>
{
	
};

#endif

