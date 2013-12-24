#include "grouppregroup.h"

AbelianType PrgGrpMorphism::translate(const ComplexType &t)
{
    AbelianType res;
    for(ComplexType::const_iterator it = t.begin();
            it != t.end(); it++)
    {
        int currentVal = res[it->baseType];
        if(it->exponent % 2 == 0)
            res[it->baseType] = currentVal + 1;
        else
            res[it->baseType] = currentVal - 1;
    }
    return res;
}

LexiconEntry<AbelianType> PrgGrpMorphism::translate(const LexiconEntry<ComplexType> &entry)
{
    LexiconEntry<AbelianType> res;
    for(LexiconEntry<ComplexType>::const_iterator it = entry.begin();
            it != entry.end(); it++)
    {
        res[PrgGrpMorphism::translate(it->first)] = it->second;
    }
    return res;
}

Lexicon<AbelianType> PrgGrpMorphism::translate(const Lexicon<ComplexType> &lex)
{
    Lexicon<AbelianType> res;
    for(Lexicon<ComplexType>::const_iterator it = lex.begin();
            it != lex.end(); it++)
    {
        res[it->first] = PrgGrpMorphism::translate(it->second);
    }
    return res;
}

