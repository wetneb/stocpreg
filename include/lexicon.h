#ifndef INCLUDED_LEXICON_H
#define INCLUDED_LEXICON_H

#include <map>
#include <string>
#include <fstream>
#include <cmath> // for lgamma

#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "pregroup.h"
#include "lexiconentry.h"

template<class T>
class Lexicon : public std::map<std::string, LexiconEntry<T> >
{
    friend class boost::serialization::access;

    public:
        //! Load a lexicon from a file, or an empty one if no path provided
        Lexicon(string filename = "")	
        {
            if(filename.size())
                load(filename);
            // TODO raise exception on error
        }

        //! Load a lexicon from a file
        bool load(string filename)
        {
            // TODO catch exceptions
            std::ifstream file(filename.c_str());

            {
                boost::archive::text_iarchive ar(file);

                ar >> *this;
            }

            return true;
        }


        //! Save it to a file
        void save(string filename)
        {
            std::ofstream file(filename.c_str());

            {
                boost::archive::text_oarchive ar(file);

                ar << *this;
            }
        }

        //! Normalize the probabilities for each word
        void normalize(float dirichletPrior = 1.0)
        {
            for(typename Lexicon<T>::iterator it = this->begin();
                    it != this->end(); it++)
                it->second.normalize(dirichletPrior);
        }

        //! Print it to a string
        string toString() const
        {
            ostringstream out;

            for(typename Lexicon<T>::const_iterator it = this->begin();
                    it != this->end(); it++)
                out << it->first << "\n" << it->second.toString() << "\n";

            return out.str();
        }

    private:
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            std::map<std::string, LexiconEntry<T> >* ptr = this;
            ar & *ptr;
        }

};

#endif

