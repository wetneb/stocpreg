#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <string>

#include "ccg.h"
#include "pregroupccg.h"

using namespace std;


vector<pair<string, CCGCat*> > parseCCGBankLine(string &line)
{
    int idx = 0;
    vector<pair<string, CCGCat*> > result;
    while(idx < line.size())
    {
        while(idx+1 < line.size() && line.substr(idx,2) != "<L")
            ++idx;
        if(idx+1 == line.size())
            break;

        idx += 3;

        int leafStart = idx;
        while(idx < line.size() && line[idx] != '>')
            idx++;

        istringstream s(line.substr(leafStart,idx-leafStart).c_str());
        string type, pos1, pos2, word, deps;
        s >> type;
        s >> pos1;
        s >> pos2;
        s >> word;
        s >> deps;

        result.push_back(make_pair(word, CCGCat::parse(type)));
    }
    return result;
}

int main(int argc, char** argv)
{
    string ccgline;
    getline(cin, ccgline);
    vector<pair<string, CCGCat*> > assignments = parseCCGBankLine(ccgline);

    for(vector<pair<string, CCGCat*> >::iterator it = assignments.begin();
            it != assignments.end(); ++it)
    {
        const CCGCat* category = it->second;
        ComplexType translated = GrammarMorphism<CCGCat*,ComplexType>::translateType(category);
        cout << it->first << " : " << it->second->toString() << " : " << translated.toString() << endl;
        delete it->second;
    }

    return 0;
}
