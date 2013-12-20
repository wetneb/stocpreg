
#include "lexicon.h"

template<class T>
Lexicon<T>::Lexicon(string filename)
{
    if(filename.size())
        load(filename);
    // TODO raise exception on error
}

template<class T>
bool Lexicon<T>::load(string filename)
{
    // TODO catch exceptions
    std::ifstream file(filename.c_str());

    {
        boost::archive::text_iarchive ar(file);

        ar >> *this;
    }

    return true;
}

template<class T>
void Lexicon<T>::save(string filename)
{
    std::ofstream file(filename.c_str());

    {
        boost::archive::text_oarchive ar(file);

        ar << *this;
    }
}

template<class T>
void Lexicon<T>::normalize(float dirichletPrior)
{
    for(typename Lexicon<T>::iterator it = this->begin();
            it != this->end(); it++)
        it->second.normalize(dirichletPrior);
}

template<class T>
string Lexicon<T>::toString() const
{
    ostringstream out;

    for(typename Lexicon<T>::const_iterator it = this->begin();
            it != this->end(); it++)
        out << it->first << "\n" << it->second.toString() << "\n";

    return out.str();
}

template<class T>
LexiconEntry<T>::LexiconEntry()
{
    ;
}

template<class T>
char LexiconEntry<T>::nthBaseType(int n)
{
    return (n == 0 ? 's' : 'a' + (n-1));
}

template<class T>
void LexiconEntry<T>::normalize(float dirichletPrior)
{
    float sum = 0;
    bool unitExcluded = false;
    for(typename LexiconEntry<T>::iterator it = this->begin();
            it != this->end(); it++)
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
        for(typename LexiconEntry<T>::iterator it = this->begin();
                it != this->end(); it++)
            if(!(unitExcluded && it->first.isUnit()))
                it->second /= sum;
    }
}

template<class T>
void LexiconEntry<T>::addCount(T t, float value)
{
    if(this->find(t) != this->end())
    {
        float oldval = (*this)[t];
        erase(t);
        (*this)[t] = oldval + value;
    }
    else
        (*this)[t] = value;
}

template<class T>
string LexiconEntry<T>::toString() const
{
    ostringstream out;

    for(typename LexiconEntry<T>::const_iterator it = this->begin();
            it != this->end(); it++)
        out << it->first.toString() << " : " << it->second << "\n";

    return out.str();
}

template<class T>
bool LexiconEntry<T>::fromFile(const string &filename)
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

