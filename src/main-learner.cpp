
#include "lexicon.h"
#include "learning.h"
#include "pregroup.h"

#include <boost/archive/text_oarchive.hpp>

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    SimpleType s("s", 0), n("n",0), nl("n",-1), nr("n",1), unit("1",0);


	if(argc != 4 && argc != 5)
	{
	    cerr << "Usage:\n"
		 << argv[0] << " [types] [sentences] [nb-iterations] (verbosity)\n"
		 << endl;
	    return 1;
	}
    bool verbose = (argc == 5);

    vector<list<string> > sentences;
    ifstream sentFile(argv[2]);
    if(!sentFile.good())
    {
        cerr << "Error while reading the file \""<<argv[2]<<"\""<<endl;
        return 1;
    }

    int nbIterations = 1;
    istringstream arg2(argv[3]);
    arg2 >> nbIterations;

    LexiconEntry defaultEntry;
    if(!defaultEntry.fromFile(argv[1]))
    {
        cerr << "Error while reading the file \""<<argv[1]<<"\""<<endl;
        return 1;
    }

    if(verbose)
    {
        cout << "Default lexicon:"<<endl
            <<defaultEntry.toString()<<endl;
    }

    Lexicon lex;

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
            {
                lex[currentWord] = defaultEntry;
			    sentence.push_back(currentWord);
            }
		}
        if(sentence.size() > 0)
            sentences.push_back(sentence);
    }

    /*
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
    entry[n] = 1.0 / 4;
    entry[nsn] = 1.0 / 4;
    entry[ns] = 1.0 / 4;
    entry[unit] = 1.0 / 4;
    for(unsigned int i = 0; i < words.size(); i++)
        lex[words[i]] = entry;
        */
    LexiconLearner learner(lex);
    Lexicon finalLex = learner.run(sentences, nbIterations, verbose);

    ofstream outLexicon("trained_lexicon");
    outLexicon << finalLex.toString() << endl;
    outLexicon.close();

	return 0;
}

