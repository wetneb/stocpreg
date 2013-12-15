
#include "lexicon.h"
#include "learning.h"
#include "pregroup.h"

#include <boost/archive/text_oarchive.hpp>

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    SimpleType s("s", 0), n("n",0), nl("n",-1), nr("n",1);


	if(argc != 2)
	{
	    cerr << "Usage:\n"
		 << argv[0] << " [sentences]\n"
		 << endl;
	    return 1;
	}

    vector<list<string> > sentences;
    ifstream sentFile(argv[1]);
    if(!sentFile.good())
    {
        cerr << "Error while reading the file \""<<argv[1]<<endl;
        return 1;
    }

	while(sentFile.good())
	{
		string line;
		getline(sentFile, line);

		istringstream inputWords(line);
		list<string> sentence;
		string currentWord;
		while(inputWords.good())
		{
			inputWords >> currentWord;
            if(currentWord != "")
			    sentence.push_back(currentWord);
		}
        if(sentence.size() > 0)
            sentences.push_back(sentence);
    }

	Lexicon lex; //(argv[1])

    ComplexType nsn(nr);
    nsn.push_back(s);
    nsn.push_back(nl);

    ComplexType ns(nr);
    ns.push_back(s);

    vector<string> words;
    words.push_back("John");
    words.push_back("Mary");
    words.push_back("bothers");
    words.push_back("walks");

    LexiconEntry entry;
    entry[n] = 1.0 / 3;
    entry[nsn] = 1.0 / 3;
    entry[ns] = 1.0 / 3;
    for(unsigned int i = 0; i < words.size(); i++)
        lex[words[i]] = entry;

    LexiconLearner learner(lex);
    Lexicon finalLex = learner.run(sentences, 1);

    cout << finalLex.toString() << endl;

	return 0;
}

