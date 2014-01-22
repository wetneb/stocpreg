#ifndef INCLUDED_PREGROUPCCG_H
#define INCLUDED_PREGROUPCCG_H

#include "ccg.h"
#include "pregroup.h"
#include "lexiconentry.h"
#include "lexicon.h"

template<>
ComplexType PrgGrpMorphism::translateType<CCGCat*,ComplexType>(const CCGCat* &t);

#endif
