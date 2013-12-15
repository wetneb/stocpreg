#ifndef INCLUDED_LEXICON_H
#define INCLUDED_LEXICON_H

#include <map>
#include <string>
#include <fstream>

#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "pregroup.h"

class LexiconEntry : public std::map<ComplexType, float>
{
    friend class boost::serialization::access;
    public:
        LexiconEntry();

        //! Build a lexicon with lots of types in it, namely all the types made of
        // - at most maxLength simple types
        // - nbBaseTypes distinct base types
        // - order at most maxOrder
        // if atLeastOneProductive is set, then all the complex types contain at least
        // one productive type.
        LexiconEntry(int nbBaseTypes, int maxLength, int maxOrder, bool atLeastOneProductive = true);

        void addCount(ComplexType t, float value);
        void normalize();
        
        string toString() const;
        bool fromFile(const string &filename); // this does not use boost serialization

    private:
        //! returns 's', 'a', 'b', 'c', …
        char nthBaseType(int n);
        //! recursive subroutine used to generate large lexicons
        void genComplexType(ComplexType base, int remainingSimple, int nbBaseTypes, int maxOrder, bool productiveIncluded);

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            std::map<ComplexType, float>* ptr = this;
            ar & *ptr;
        }
};

class Lexicon : public std::map<std::string, LexiconEntry>
{
    friend class boost::serialization::access;

    public:
        //! Load a lexicon from a file, or an empty one if no path provided
        Lexicon(string filename = "");	

        //! Load a lexicon from a file
        bool load(string filename);

        //! Save it to a file
        void save(string filename);

        //! Normalize the probabilities for each word
        void normalize();

        //! Print it to a string
        string toString() const;

    private:
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            std::map<std::string, LexiconEntry>* ptr = this;
            ar & *ptr;
        }

};

#endif

