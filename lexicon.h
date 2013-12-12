#ifndef INCLUDED_LEXICON_H
#define INCLUDED_LEXICON_H

#include <map>
#include <boost/serialization/map.hpp>
#include "pregroup.h"

class LexiconEntry : public std::map<ComplexType, float>
{
		
};

class Lexicon : public std::map<std::string, LexiconEntry>
{
	
};

#endif

