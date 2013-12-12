#ifndef INCLUDED_LEXICON_H
#define INCLUDED_LEXICON_H

#include <map>
#include <string>

#include <boost/serialization/map.hpp>

#include "pregroup.h"

class LexiconEntry : public std::map<ComplexType, float>
{
		
};

class Lexicon : public std::map<std::string, LexiconEntry>
{
    public:
        //! Load a lexicon from a file
        Lexicon(string filename);	
};

#endif

