
#include "lexicon.h"
#include "parser.h"
#include "pregroup.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
	    cerr << "Usage:\n"
		 << argv[0] << " [lexicon]\n"
		 << endl;
	    return 1;
	}

	Lexicon lex(argv[1]);

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

		SimpleType sType("s",0);
		FrameString fs(lex, sentence, sType);

		SPGParser parser(fs);
		cout << parser.run() << endl;
	}

	return 0;
}

