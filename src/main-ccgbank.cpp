#include <iostream>

#include "ccg.h"

using namespace std;

int main(int argc, char** argv)
{
    string type;
    cin >> type;
    CCGCat* cat = CCGCat::parse(type);
    cout << cat->toString() << endl;
    delete cat;
    return 0;
}
