
#ifndef INCLUDED_FRAMESTRING_H
#define INCLUDED_FRAMESTRING_H

#include <vector>
#include <list>
#include <sstream>

class FrameString;

#include "frameelem.h"
#include "lexicon.h"
#include "pregroup.h"

using namespace std;

class FrameString : public vector<FrameElem>
{
    public:
	//! Construct an empty frame string
	FrameString();

	//! Construct from a list of words, a lexicon and a target type
	FrameString(Lexicon lex, list<string> words, ComplexType target);	

	string toString();
	
	//! Get the probability associated to some complex type.
	// The position argument indicates the index of the first simple
	// type in the complex type. 
	float getProba(int position);

    protected:
	void addLB();

	void addRB();

	void addStar();

	void addSimpleType(SimpleType t);

	void addType(ComplexType t, float proba);

     private:
	map<int, float> mProba;
};

#endif

