
#include "grouppregroup.h"

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        cerr << "Usage:" << endl
            << argv[0] << " [pregroup_file_name]"<<endl
            << "Where the lexicon is a file containing a list of pregroup types."<< endl
            << "Output: the image of this set of pregroup types under the forgetful morphism." << endl;
        return 1;
    }

    LexiconEntry<ComplexType> defaultEntry;
    if(!defaultEntry.fromFile(argv[1]))
    {
        cerr << "Error while reading the file \""<<argv[1]<<"\""<<endl;
        return 1;
    }

    LexiconEntry<AbelianType> translated = PrgGrpMorphism::translate(defaultEntry);

    cout << translated.toString() << flush;

    return 0;
}

