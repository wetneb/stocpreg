
#include "lexicon.h"

template<class Archive>
void LexiconEntry::serialize(Archive &ar, const unsigned int version)
{
    std::map<ComplexType, float>* ptr = this;
    ar & *ptr;
}


Lexicon::Lexicon(string filename)
{
    std::ifstream file(filename.c_str());

    {
        boost::archive::text_iarchive ar(file);

       ar >> *this;
    }
}

void Lexicon::save(string filename)
{
    std::ofstream file(filename.c_str());

    {
        boost::archive::text_oarchive ar(file);

        ar << *this;
    }
}

template<class Archive>
void Lexicon::serialize(Archive &ar, const unsigned int version)
{
    std::map<std::string, LexiconEntry>* ptr = this;
    ar & *ptr;
}

