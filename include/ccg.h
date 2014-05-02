
#ifndef INCLUDED_CCG_H
#define INCLUDED_CCG_H

#include <string>
#include <utility>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <exception>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/utility.hpp>

using namespace std;

class CCGCat;
class CCGLabel;
class CCGQuotient;
class CCGTypeError;

class CCGTypeError : public exception
{
    public:
        CCGTypeError(string what);
        const char* what() const throw ();
        ~CCGTypeError() throw ();
    private:
        string mWhat;
};

class CCGCat
{
    public:
        virtual bool isLabel() const
        {
            return false;
        }

        virtual bool isQuotient() const
        {
            return false;
        }

        virtual bool isLeft() const
        {
            return false;
        }

        virtual bool isRight() const
        {
            return false;
        }

        virtual string toString(bool annotations = true) const
        {
            return "<null>";
        }

        static CCGCat* parse(string str);
    private:
        static pair<CCGCat*,int> parseLeast(string &str, int start);
};

class CCGLabel : public CCGCat
{
    public:
        CCGLabel(string mainType, string annotation);

        string mainType;
        string annotation;

        string toString(bool annotations = true) const;
        bool isLabel() const;
};

class CCGQuotient : public CCGCat
{
    public:
        // right = true corresponds to /
        CCGQuotient(CCGCat* num, CCGCat* denom, bool right);
        ~CCGQuotient();

        const CCGCat* num;
        const CCGCat* denom;
        const bool right;

        string toString(bool annotations = true) const;
        bool isQuotient() const;
        bool isLeft() const;
        bool isRight() const;
};

#endif

