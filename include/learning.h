
#ifndef INCLUDED_LEARNING_H
#define INCLUDED_LEARNING_H

#include "lexicon.h"
#include "parser.h"

#include <vector>
#include <list>

using namespace std;

class LexiconLearner
{
    public:
        LexiconLearner(Lexicon &initLex);

        Lexicon run(vector<list<string> > &sentences, int nbIterations);        

    private:
        Lexicon mLex;

};

#endif

