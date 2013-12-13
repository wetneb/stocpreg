#include "framestring.h"


//! Construct an empty frame string
FrameString::FrameString()
{

}

FrameString::FrameString(const FrameString &rhs) :
    vector<FrameElem*>()
{
    reserve(rhs.size());
    for(FrameString::iterator it = begin();
            it != end(); it++)
        push_back((*it)->clone());
    cout << "CLONED" << endl;
}

//! Destructor
FrameString::~FrameString()
{
    for(FrameString::iterator it = begin();
            it != end(); it++)
        delete (*it);
    cout << "DELETED" << endl;
}

//! Construct from a list of words, a lexicon and a target type
FrameString::FrameString(Lexicon lex, list<string> words, ComplexType target)
{
	for(list<string>::iterator word = words.begin();
		word != words.end(); word++)
	{
		addLB();
		addStar();
		
		if(lex.count(*word))
		{
			LexiconEntry entry = lex.find(*word)->second;
			for(LexiconEntry::iterator it = entry.begin();
				it != entry.end(); it++)
			{
				addType(it->first, it->second);
				addStar();
			}
		}	

		addRB();
	}

    addLB();
    addStar();
    addType(target.rightAdjoint(), 1.0);
}

string FrameString::toString()
{
	ostringstream out;

	for(FrameString::iterator elem = begin();
		elem != end(); elem++)
	    out << (*elem)->toString();

	return out.str();
}

//! Get the probability associated to some complex type.
// The position argument indicates the index of the first simple
// type in the complex type. 
float FrameString::getProba(int position)
{
    if(mProba.count(position))
    	return mProba[position];

    return 1.0;
}

void FrameString::addLB()
{
    push_back(new LBElem());
}

void FrameString::addRB()
{
    push_back(new RBElem());
}

void FrameString::addStar()
{
    push_back(new StarElem());
}

void FrameString::addSimpleType(SimpleType t)
{
    push_back(new TypeElem(t));
}

void FrameString::addType(ComplexType t, float proba)
{
    int beginning = size();
    for(ComplexType::iterator it = t.begin();
	    it != t.end(); it++)
    {
	    addSimpleType(*it);
    }

    mProba[beginning] = proba;
}


