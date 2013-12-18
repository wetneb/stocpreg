
#include "lexicon.h"

Lexicon::Lexicon(string filename)
{
    if(filename.size())
        load(filename);
    // TODO raise exception on error
}

bool Lexicon::load(string filename)
{
    // TODO catch exceptions
    std::ifstream file(filename.c_str());

    {
        boost::archive::text_iarchive ar(file);

        ar >> *this;
    }

    return true;
}

void Lexicon::save(string filename)
{
    std::ofstream file(filename.c_str());

    {
        boost::archive::text_oarchive ar(file);

        ar << *this;
    }
}

void Lexicon::normalize(float dirichletPrior)
{
    for(Lexicon::iterator it = begin();
            it != end(); it++)
        it->second.normalize(dirichletPrior);
}

string Lexicon::toString() const
{
    ostringstream out;

    for(Lexicon::const_iterator it = begin();
            it != end(); it++)
        out << it->first << "\n" << it->second.toString() << "\n";

    return out.str();
}

LexiconEntry::LexiconEntry()
{
    ;
}

void LexiconEntry::genComplexType(ComplexType base, int remainingSimple, int nbBaseTypes, int maxOrder, bool productiveIncluded)
{
    if(remainingSimple == 0)
    {
        if(productiveIncluded)
           (*this)[base] = 1.0;
    }
    else
    {
        for(int exp = -maxOrder; exp <= maxOrder; exp++)
        {
            for(int bt = 0; bt < nbBaseTypes; bt++)
            {
                ComplexType ct(base);
                ct.push_back(SimpleType(string(1,nthBaseType(bt)),exp));
                genComplexType(ct, remainingSimple-1, nbBaseTypes, maxOrder, productiveIncluded || (exp % 2 == 0));
            }
        }
    }
}

//! Build a lexicon with lots of types in it, namely all the types made of
// - at most maxLength simple types
// - nbBaseTypes distinct base types
// - order at most maxOrder
// if atLeastOneProductive is set, then all the complex types contain at least
// one productive type.
LexiconEntry::LexiconEntry(int nbBaseTypes, int maxLength, int maxOrder, bool atLeastOneProductive)
{
    for(int length = 1; length <= maxLength; length++)
    {
        ComplexType ct;
        genComplexType(ct, length, nbBaseTypes, maxOrder, !atLeastOneProductive);
    }
    normalize();
}

char LexiconEntry::nthBaseType(int n)
{
    return (n == 0 ? 's' : 'a' + (n-1));
}

void LexiconEntry::normalize(float dirichletPrior)
{
    float sum = 0;
    bool unitExcluded = false;
    for(LexiconEntry::iterator it = begin();
            it != end(); it++)
    {
        if(it->first.isUnit())
            it->second += dirichletPrior - 1;
        if(it->second < 0)
        {
            it->second = 0;
            unitExcluded = true;
        }
        else
            sum += it->second;
    }

    if(sum > 0)
    {
        for(LexiconEntry::iterator it = begin();
                it != end(); it++)
            if(!(unitExcluded && it->first.isUnit()))
                it->second /= sum;
    }
}

void LexiconEntry::addCount(ComplexType t, float value)
{
    if(find(t) != end())
    {
        float oldval = (*this)[t];
        erase(t);
        (*this)[t] = oldval + value;
    }
    else
        (*this)[t] = value;
}

string LexiconEntry::toString() const
{
    ostringstream out;

    for(LexiconEntry::const_iterator it = begin();
            it != end(); it++)
        out << it->first.toString() << " : " << it->second << "\n";

    return out.str();
}

bool LexiconEntry::fromFile(const string &filename)
{ // this does not use boost serialization
    ifstream fs(filename.c_str());
    if(!fs.good())
        return false;
    
    while(fs.good())
    {
        string line;
        getline(fs, line);
        if(line.size())
        {
            ComplexType ct;
            if(!ct.fromString(line))
            {
                cerr << "Error while parsing the complex type \""<<line<<"\""<<endl;
                return false;
            }
            (*this)[ct] = 1.0;
        }
    }
    normalize();    
}

