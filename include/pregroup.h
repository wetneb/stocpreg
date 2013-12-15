
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
	    static bool strictlyLess(const string &lhs, const string &rhs);

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
    public:
    	SimpleType(string baseType = "", int exponent = 0);

        //! Is this type less than this other type ?
	    bool lessThan(const SimpleType &rhs) const;
        bool strictlyLessThan(const SimpleType &rhs) const;
        bool operator<(const SimpleType &rhs) const;

        //! Generalized Constraction rule
        bool gcon(const SimpleType &rhs) const;
        //! Is this type the pregroup unit ?
	    bool isUnit() const;

        //! Get the left adjoint of this type
        SimpleType leftAdjoint() const;
        //! Get the right adjoint of this type
        SimpleType rightAdjoint() const;

        string toString() const;
        bool fromString(const string &str);

	    int exponent;
	    string baseType;


    private:
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            ar & baseType;
            ar & exponent;
        }
};

// A product of basic types
class ComplexType : public list<SimpleType>
{
    public:
        ComplexType();
        ComplexType(SimpleType t);

        // Adjoints
        ComplexType leftAdjoint() const;
        ComplexType rightAdjoint() const;

        //! Defined only for data storage purposes
        bool operator<(const ComplexType &rhs) const;
//        bool operator==(const ComplexType &rhs) const;

	    string toString() const;
        bool fromString(const string &str);
        
    private: 
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            std::list<SimpleType>* ptr = this;
            ar & *ptr;
        }
};

#endif

