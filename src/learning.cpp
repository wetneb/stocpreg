
#include "learning.h"

LexiconLearner::LexiconLearner(Lexicon &initLex) :
    mLex(initLex)
{
    ;
}

Lexicon LexiconLearner::run(vector<list<string> > &sentences, int nbIterations)
{
    SimpleType targetType("s", 0);

    for(int i = 0; i < nbIterations; i++)
    {
        Lexicon counts;

        cout << "ITERATION "<<i+1<<endl;

        // Parsing and counting
        for(unsigned int s = 0; s < sentences.size(); s++)
        {
            FrameString fs(mLex, sentences[s], targetType);
            cout << fs.toString() << endl;

            SPGParser ps(fs);
            cout << "Probability : "<<ps.run()<<endl;
            set<Assignment> as = ps.getAssignments();
            for(set<Assignment>::iterator it = as.begin();
                    it != as.end(); it++)
            {
                Assignment a = *it;
                float proba = ps.proba(a);
                list<string>::iterator word = sentences[s].begin();
                cout << "Assignment : "<<endl;
                for(Assignment::iterator typ = a.begin();
                        typ != a.end(); typ++)
                {
                    if(word != sentences[s].end())
                    {
                        cout << *word << " -> "<< fs.getType(*typ).toString() << " (type id "<<*typ<<")"<<endl;
                        counts[*word].addCount(fs.getType(*typ), proba);
                        word++;
                    }
                }
            }
            cout << endl;
        }

        // Normalizing
        counts.normalize();
        mLex = counts;
    }

    return mLex;
}


