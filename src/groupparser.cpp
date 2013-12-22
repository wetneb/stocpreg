#include "groupparser.h"

GroupParser::GroupParser(list<string> &sentence, Lexicon<AbelianType> &lex) :
    mLex(lex)
{
    for(list<string>::iterator it = sentence.begin();
            it != sentence.end(); it++)
        mSentence.push_back(*it);
}

float GroupParser::run()
{
    int n = mSentence.size();
    /*
    int sep = n/2;
    map<AbelianType, set<GrpAssignment> >
        *valuesLeft = doProducts(0, sep),
        *valuesRight = doProducts(sep, n);

    ...

    delete valuesLeft;
    delete valuesRight;
        */
    float sum = 0;
    map<AbelianType, set<GrpAssignment> >* assignments = doProducts(0,n);

    

    delete assignments;
    return sum;    
}

map<AbelianType, set<GrpAssignment> >* GroupParser::doProducts(int from, int to)
{
    map<AbelianType, set<GrpAssignment> > *values1 = new map<AbelianType, set<GrpAssignment> >();
    map<AbelianType, set<GrpAssignment> > *values2 = new map<AbelianType, set<GrpAssignment> >();

    set<GrpAssignment> emptyAssignment;
    AbelianType unit;
    (*values1)[unit] = emptyAssignment;
    
    for(int i = from; i < to; i++)
    {
        LexiconEntry<AbelianType> &entry = mLex[mSentence[i]];
        for(map<AbelianType, set<GrpAssignment> >::iterator it = values1->begin();
                it != values1->end(); it++)
        {
            int typeIndex = 0;
            for(LexiconEntry<AbelianType>::iterator tp = entry.begin();
                    tp != entry.end(); tp++)
            {
                set<GrpAssignment> newAssign;
                for(set<GrpAssignment>::iterator s = it->second.begin();
                        s != it->second.end(); s++)
                    newAssign.insert(s->extend(typeIndex, tp->second));

                (*values2)[it->first * tp->first] = newAssign;

                typeIndex++;
            }
        }

        swap(values1, values2);
    }

    return values2;
}

GrpAssignment::GrpAssignment() :
    mProba(1.0)
{

}

GrpAssignment GrpAssignment::extend(int x, float proba) const
{
    GrpAssignment n(*this);
    n.mProba *= proba;
    n.push_back(x);
    return n;
}

