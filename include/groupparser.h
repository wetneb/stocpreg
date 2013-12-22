#ifndef INCLUDED_ABELIANPARSER_H
#define INCLUDED_ABELIANPARSER_H

#include <utility>
#include <list>
#include <set>
#include <map>
#include <vector>

#include "lexicon.h"
#include "group.h"

class GrpAssignment : public list<int>
{
    public:
        GrpAssignment();

        GrpAssignment extend(int x, float proba) const;

    private:
        float mProba;
};

class GroupParser
{
    public:
        //! Set up the parser for the sentence with types taken from the lexicon
        GroupParser(list<string> &sentence, Lexicon<AbelianType> &lex);

        //! Run the parser. Returns the probability that the sentence is grammatical
        float run();

    private:
        map<AbelianType, set<GrpAssignment> >* doProducts(int from, int to);

        Lexicon<AbelianType> &mLex;
        vector<string> mSentence;

};

#endif

