
#ifndef INCLUDED_LEARNING_H
#define INCLUDED_LEARNING_H

#include "lexicon.h"
#include "parser.h"

#include <vector>
#include <list>
#include <cmath>

using namespace std;

class LexiconLearner
{
    public:
        LexiconLearner(Lexicon<ComplexType> &initLex);

        Lexicon<ComplexType> run(vector<list<string> > &sentences, int nbIterations, float dirichletPrior, bool verbose);        

    private:
        Lexicon<ComplexType> mLex;

};

#endif

