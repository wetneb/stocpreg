
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

class AbelianGroup;
class AbelianType;

using namespace std;

//! Class managing comparisons between basic types
class AbelianGroup : public set<pair<string,string> >
{
	public:
	    static bool less(const string &lhs, const string &rhs);
	    static bool strictlyLess(const string &lhs, const string &rhs);

        // Comparisons management
        static bool loadGroup(string filename);
        static void unloadGroup();

   private:
	    AbelianGroup();
        ~AbelianGroup();

        bool load(string filename);

	    static AbelianGroup *mGlobalAbelianGroup;
};

// An element of a group
class AbelianType : public map<string, int>
{
    public:
        AbelianType();
        AbelianType(string baseType, int exponent = 1);

        // Inverse
        AbelianType inverse() const;

        bool isUnit() const;

        AbelianType operator*(const AbelianType &rhs) const;

        //! Defined only for data storage purposes
        bool operator<(const AbelianType &rhs) const;
//        bool operator==(const ComplexType &rhs) const;

	    string toString() const;
        bool fromString(const string &str);
        
    private: 
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            std::map<string, int>* ptr = this;
            ar & *ptr;
        }
};

#endif

