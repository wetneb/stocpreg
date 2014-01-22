#include "grouppregroup.h"

template<>
AbelianType translateType<ComplexType,AbelianType>(const ComplexType &t)
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

