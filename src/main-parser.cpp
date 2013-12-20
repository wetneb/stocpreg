
#include "lexicon.h"
#include "parser.h"
#include "pregroup.h"

#include <boost/archive/text_oarchive.hpp>

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    SimpleType s("s", 0), n("n",0), nl("n",-1), nr("n",1);

    ComplexType sn(s);
    sn.push_back(n);

    LexiconEntry<ComplexType> lex1;
    lex1[sn] = 0.7;
    Lexicon<ComplexType> lex2;
    lex2["Alice"] = lex1;

/*
	if(argc != 2)
	{
	    cerr << "Usage:\n"
		 << argv[0] << " [lexicon]\n"
		 << endl;
	    return 1;
	}
*/

	Lexicon<ComplexType> lex; //(argv[1])

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

    LexiconEntry<ComplexType> entry;
    entry[n] = 1.0 / 3;
    entry[nsn] = 1.0 / 3;
    entry[ns] = 1.0 / 3;
    for(unsigned int i = 0; i < words.size(); i++)
        lex[words[i]] = entry;


    SimpleType sType("s",0);

	while(cin.good())
	{
		string line;
		getline(cin, line);

		istringstream inputWords(line);
		list<string> sentence;
		string currentWord;
		while(inputWords.good())
		{
			inputWords >> currentWord;
			sentence.push_back(currentWord);
		}

		FrameString fs(lex, sentence, sType);
        cout << fs.toString() << endl;

		SPGParser parser(fs);
		cout << parser.run() << endl;
	}

	return 0;
}

