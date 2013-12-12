
#ifndef INCLUDED_PREGROUP_H
#define INCLUDED_PREGROUP_H

#include <string>
#include <utility>
#include <set>
#include <map>
#include <string>
#include <sstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/utility.hpp>

class Pregroup;
class SimpleType;
class ComplexType;

using namespace std;

//! Class managing comparisons between basic types
class Pregroup : public set<pair<string,string> >
{
	public:
	    static bool less(const string &lhs, const string &rhs);

        // Comparisons management
        static bool loadPregroup(string filename);
        static void unloadPregroup();

   private:
	    Pregroup();
        ~Pregroup();

        bool load(string filename);

	    static Pregroup *mGlobalPregroup;
};

//! A basic type with an exponent
class SimpleType
{
    friend class boost::serialization::access;

    public:
    	SimpleType(string baseType, int exponent);

	    bool operator<=(const SimpleType &rhs) const;
        //! Generalized Constraction rule
        bool gcon(const SimpleType &rhs) const;
        //! Is this type the pregroup unit ?
	    bool isUnit() const;

        //! Get the left adjoint of this type
        SimpleType leftAdjoint() const;
        //! Get the right adjoint of this type
        SimpleType rightAdjoint() const;

        string toString() const;

	    int exponent;
	    string baseType;


    private:
        template<class Archive>
	    void serialize(Archive &ar, const unsigned int version);
};

// A product of basic types
class ComplexType : public list<SimpleType>
{
    friend class boost::serialization::access;

    public:
        ComplexType();
        ComplexType(SimpleType t);

	    string toString() const;
        
    private: 
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version);
};

#endif

