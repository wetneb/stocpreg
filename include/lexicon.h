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

    private:
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version);
};

class Lexicon : public std::map<std::string, LexiconEntry>
{
    friend class boost::serialization::access;

    public:
        //! Load a lexicon from a file
        Lexicon(string filename);	

        //! Save it to a file
        void save(string filename);

    private:
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version);
};

#endif

