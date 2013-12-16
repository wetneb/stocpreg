
#include "learning.h"

LexiconLearner::LexiconLearner(Lexicon &initLex) :
    mLex(initLex)
{
    ;
}

Lexicon LexiconLearner::run(vector<list<string> > &sentences, int nbIterations, bool verbose)
{
    SimpleType targetType("s", 0);

    for(int i = 0; i < nbIterations; i++)
    {
        /*
        if(i > 0)
            verbose = false;
        // */

        Lexicon counts;

        cout << "ITERATION "<<i+1<<endl;
        float logLikelihood = 0;

        // Parsing and counting
        for(unsigned int s = 0; s < sentences.size(); s++)
        {
            FrameString fs(mLex, sentences[s], targetType);
            if(verbose)
                cout << fs.toString() << endl;

            SPGParser ps(fs);
            float totalProba = ps.run();
            if(verbose)
                cout << "Probability : "<<totalProba<<endl;
            set<Assignment> as = ps.getAssignments();
            for(set<Assignment>::iterator it = as.begin();
                    it != as.end(); it++)
            {
                Assignment a = *it;
                float proba = ps.proba(a);
                list<string>::iterator word = sentences[s].begin();
                if(verbose)
                    cout << "Assignment (proba "<<proba<<"): "<<endl;
                for(Assignment::iterator typ = a.begin();
                        typ != a.end(); typ++)
                {
                    if(word != sentences[s].end())
                    {
                        if(verbose)
                            cout << *word << " -> "<< fs.getType(*typ).toString() << " (type id "<<*typ<<")"<<endl;
                        counts[*word].addCount(fs.getType(*typ), proba);
                        word++;
                    }
                }
            }
            if(verbose)
                cout << endl;
            else cout << "." << flush;

            logLikelihood += log(totalProba);
        }
        if(!verbose)
            cout << endl;

        // Normalizing
        counts.normalize();

        mLex = counts;
        
        cout << "Perplexity (before last step): "<<-logLikelihood<<endl;
    }

    return mLex;
}


