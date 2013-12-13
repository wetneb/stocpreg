
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


