#ifndef INCLUDED_LEXICONENTRY_H
#define INCLUDED_LEXICONENTRY_H

#include <map>
#include <string>
#include <fstream>
#include <cmath> // for lgamma

#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "pregroup.h"

template<class T>
class LexiconEntry : public std::map<T, float>
{
    friend class boost::serialization::access;
    public:
        LexiconEntry()
        {
            ;
        }

        void addCount(T t, float value)
        {
            if(this->find(t) != this->end())
            {
                float oldval = (*this)[t];
                this->erase(t);
                (*this)[t] = oldval + value;
            }
            else
                (*this)[t] = value;
        }


        void normalize(float dirichletPrior = 1.0)
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
        
        string toString() const
        {
            ostringstream out;

            for(typename LexiconEntry<T>::const_iterator it = this->begin();
                    it != this->end(); it++)
                out << it->first.toString() << " : " << it->second << "\n";

            return out.str();
        }

        bool fromFile(const string &filename) // this does not use boost serialization
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

    private:
        //! returns 's', 'a', 'b', 'c', …
        char nthBaseType(int n)
        {
            return (n == 0 ? 's' : 'a' + (n-1));
        }

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            std::map<ComplexType, float>* ptr = this;
            ar & *ptr;
        }
};

#endif

