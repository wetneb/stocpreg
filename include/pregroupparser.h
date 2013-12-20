
#ifndef INCLUDED_PRGPARSER_H
#define INCLUDED_PRGPARSER_H

#include "lexicon.h"
#include "pregroup.h"
#include "framestring.h"

#include <set>
#include <vector>

class SPGParser;
class Assignment;

using namespace std;

class Assignment : public set<int>
{
    public:
        //! Create a singleton
        static Assignment singleton(int val);

        //! Create the union with another set
        Assignment createUnion(const Assignment &rhs) const;
};


class SPGParser
{
	public:
	    // Set up the parser for the following frame string
	    SPGParser(FrameString &fs);

	    // Run the parser and get the probability that the whole
	    // string is reductible.
	    float run();

        //! Retrieve the set of assignments making the sentence valid
        set<Assignment> getAssignments();
        //! What is the probability of this type assignment ?
        float proba(Assignment a);
        //! What is the probability of this set of type assignments ?
        float proba(set<Assignment> s);

	private:
	    // Is there an assignment making the substring [i;j]
	    // reductible ?
	    bool reductible(int i, int j);

	    // Do actually the computation
	    set<Assignment> computeReductible(int i, int j);

	    /// HELPERS
	    
	    FrameElem* get(int pos);
	    SimpleType at(int pos);
	    bool isType(int pos);
	    bool isLB(int pos);
	    bool isRB(int pos);
	    bool isStar(int pos);
	    bool isUnit(int pos);
	    //! Does the Generalized Contraction rule applies ?
	    bool gcon(int i, int j);
        //! What is the probability that this type has been assigned ?
        float proba(int i);
        //! Do the product of two assignment sets :
        // A x B = { a u b, a \in A, b \in B }
        static set<Assignment> product(const set<Assignment> &a, const set<Assignment> &b);

	    // MEMBERS
	   
	    FrameString frame;

	    // frame.size()
	    int n;

        //! Smallest index k such that frame[j] is a type for k <= j <= i (if defined)
        vector<int> headType;

        // type assignments that make [i;j] reduce to 1
        vector<vector<set<Assignment> > > assignments;

        // has this set of assignments already been computed ?
        vector<vector<bool> > computed;

	    // index of words
	    vector<int> widx;
};

#endif

