
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


	if(argc != 5 && argc != 6)
	{
	    cerr << "Usage:\n"
		 << argv[0] << " [types] [sentences] [nb-iterations] [dirichlet-prior] (verbosity)\n"
		 << endl;
	    return 1;
	}
    bool verbose = (argc == 6);

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
    float dirichletPrior = 1.0;
    istringstream arg3(argv[4]);
    arg3 >> dirichletPrior;

    LexiconEntry<ComplexType> defaultEntry;
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

    Lexicon<ComplexType> lex;

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
            if(currentWord.size())
            {
                lex[currentWord] = defaultEntry;
			    sentence.push_back(currentWord);
            }
		}
        
        if(sentence.size() > 0)
            sentences.push_back(sentence);
    }

    LexiconLearner learner(lex);
    Lexicon<ComplexType> finalLex = learner.run(sentences, nbIterations, dirichletPrior, verbose);

    ofstream outLexicon("trained_lexicon");
    outLexicon << finalLex.toString() << endl;
    outLexicon.close();

	return 0;
}

