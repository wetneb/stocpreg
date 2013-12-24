#ifndef INCLUDED_GROUPPREGROUP_H
#define INCLUDED_GROUPPREGROUP_H

#include "group.h"
#include "pregroup.h"
#include "lexiconentry.h"
#include "lexicon.h"

class PrgGrpMorphism
{
    public:
        //! Image of a complex type under the canonical forgetful morphism
        static AbelianType translate(const ComplexType &t);
        //! Image of a lexicon entry under the same morphism
        static LexiconEntry<AbelianType> translate(const LexiconEntry<ComplexType> &entry);
        //! Image of a lexicon under the same morphism
        static Lexicon<AbelianType> translate(const Lexicon<ComplexType> &lex);
};

#endif
