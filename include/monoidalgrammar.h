
#ifndef INCLUDED_MONOIDALGRAMMAR_H
#define INCLUDED_MONOIDALGRAMMAR_H

class MonoidalGrammar;

template<class T>
class MonoidalGrammar
{
    public:
        bool grammatical(const T& sentence) const;
};

#endif

