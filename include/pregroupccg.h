#ifndef INCLUDED_PREGROUPCCG_H
#define INCLUDED_PREGROUPCCG_H

#include "ccg.h"
#include "pregroup.h"
#include "lexiconentry.h"
#include "lexicon.h"
#include "morphism.h"

template<typename T>
class GrammarMorphism<T*,ComplexType>
{
    public:
    static ComplexType translateType(const T* &t)
    {
        ComplexType res;
        if(t->isLabel())
        {
            CCGLabel* lbl = (CCGLabel*)t;
            res.push_back(SimpleType(lbl->mainType,0,lbl->annotation));
        }
        else
        {
            CCGQuotient* quo = (CCGQuotient*)t;
            ComplexType body = translateType(quo->num);
            ComplexType arg = translateType(quo->denom);
            if(quo->right)
            {
                const ComplexType &argl = arg.leftAdjoint();
                res = body * argl;
            }
            else
            {
                const ComplexType &argr = arg.rightAdjoint();
                res = argr * body;
            }
        }
        return res;
    }


};

#endif
