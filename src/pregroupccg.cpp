#include "pregroupccg.h"

template<class T>
ComplexType PrgGrpMorphism::translateType<T*,ComplexType>(const T* &t)
{
    ComplexType res;
    if(t->isLabel())
    {
        CCGLabel* lbl = (CCGLabel*)t;
        res.push_back(SimpleType(lbl->mainType, 0, lbl->annotation));
    }
    else
    {
        CCGQuotient* quo = (CCGQuotient*)t;
        ComplexType body = translateType<CCGCat*,ComplexType>(t->num);
        ComplexType arg = translateType<CCGCat*,ComplexType>(t->denom);
        if(quo->right)
        {
            ComplexType &argl = arg.leftAdjoint();
            body.splice(argl, body.end());
        }
        else
        {
            ComplexType &argr = arg.rightAdjoint();
            body.splice(argr, body.begin());
        }
        return body;
    }
    return res;
}


