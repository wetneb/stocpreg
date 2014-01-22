
#ifndef INCLUDED_MORPHISM_H
#define INCLUDED_MORPHISM_H

#include "lexiconentry.h"
#include "lexicon.h"


template<class S, class T> T translateType(const S& s);
    
template<typename S, typename T>
LexiconEntry<T> translateEntry(const LexiconEntry<S> &entry)
{
    LexiconEntry<T> res;
    for(typename LexiconEntry<S>::const_iterator it = entry.begin();
            it != entry.end(); it++)
    {
        res[translateType<S,T>(it->first)] += it->second;
    }
    return res;
}

template<class S, class T>
Lexicon<T> translateLexicon(const Lexicon<S> &lex)
{
    Lexicon<T> res;
    for(typename Lexicon<S>::const_iterator it = lex.begin();
            it != lex.end(); it++)
    {
        res[it->first] = translateEntry<S, T>(it->second);
    }
    return res;
}

#endif

