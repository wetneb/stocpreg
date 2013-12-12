
#ifndef INCLUDED_PREGROUP_H
#define INCLUDED_PREGROUP_H

#include <string>
#include <utility>
#include <set>
#include <map>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/list.hpp>
#include <boost/archive/set.hpp>
#include <boost/archive/pair.hpp>

class Pregroup;
class SimpleType;
class ComplexType;

using namespace std;

class Pregroup : public set<pair<string,string> >
{
	public:
	    Pregroup();
	
	    bool less(const string &lhs, const string &rhs) const;
};

class SimpleType
{
    friend class boost::serialization::access;

    public:
	SimpleType(string baseType, int exponent);

	bool operator<=(const SimpleType &rhs) const;
	bool isUnit() const;


	int exponent;
	string baseType;

	static Pregroup *mGlobalPregroup;

    private:
	void serialize(Archive &ar, const unsigned int version);
};

class ComplexType : public list<SimpleType>
{
	
};

#endif

