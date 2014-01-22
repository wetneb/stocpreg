#ifndef INCLUDED_GROUPPREGROUP_H
#define INCLUDED_GROUPPREGROUP_H

#include "group.h"
#include "pregroup.h"
#include "lexiconentry.h"
#include "lexicon.h"
#include "morphism.h"


template<>
class GrammarMorphism<ComplexType,AbelianType>
{
    public:
    //! Image of a complex type under the canonical forgetful morphism
    static AbelianType translateType(const ComplexType &t)
    {
        AbelianType res;
        for(ComplexType::const_iterator it = t.begin();
                it != t.end(); it++)
        {
            if(it->exponent % 2 == 0)
                res *= AbelianType(it->baseType,1);
            else
                res *= AbelianType(it->baseType,-1);
        }
        return res;
    }
};

#endif
