#ifndef INCLUDED_GROUPPREGROUP_H
#define INCLUDED_GROUPPREGROUP_H

#include "group.h"
#include "pregroup.h"
#include "lexiconentry.h"
#include "lexicon.h"
#include "morphism.h"

//! Image of a complex type under the canonical forgetful morphism
template<>
AbelianType translateType<ComplexType,AbelianType>(const ComplexType &t);

#endif
