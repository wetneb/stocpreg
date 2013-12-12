
#ifndef INCLUDED_PARSER_H
#define INCLUDED_PARSER_H

#include "lexicon.h"
#include "pregroup.h"
#include "framestring.h"

class SPGParser;

class SPGParser
{
	public:
	    // Set up the parser for the following frame string
	    SPGParser(FrameString fs);

	    // Run the parser and get the probability that the whole
	    // string is reductible.
	    float run();

	private:
	    // Compute the probability that the substring [i;j] is
	    // reductible
	    float reductible(int i, int j);

	    // Do actually the computation
	    float computeReductible(int i, int j);

	    /// HELPERS
	    
	    FrameElem get(int pos);
	    SimpleType at(int pos);
	    bool isType(int pos);
	    bool isLB(int pos);
	    bool isRB(int pos);
	    bool isStar(int pos);
	    bool isUnit(int pos);
	    // Does the Generalized Contraction rule applies ?
	    bool gcon(int i, int j);
        // What is the probability that this type has been assigned ?
        float proba(int i);

	    // MEMBERS
	   
	    FrameString frame;

	    // frame.size()
	    int n;

	    // probability that [i;j] reduces to 1
	    vector<vector<float> > redProba;

	    // index of words
	    vector<int> widx;
};

#endif

