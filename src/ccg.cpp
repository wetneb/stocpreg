

#include "ccg.h"

CCGTypeError::CCGTypeError(string what) : mWhat(what)
{

}

CCGTypeError::~CCGTypeError() throw ()
{

}

const char* CCGTypeError::what() const throw ()
{
    return mWhat.c_str();
}

CCGCat* CCGCat::parse(string str)
{
    if(str.size() == 0)
        throw CCGTypeError("Unable to parse the empty string");

    pair<CCGCat*,int> res = parseLeast(str,0);
    if(res.second == str.size())
        return res.first;
    else throw CCGTypeError("Trailing characters at the end of the type: \""+str.substr(res.second)+"\"");
}

bool admissibleCharForType(char c)
{
    return isalpha(c)
        || c == ','
        || c == '.'
        || c == ':'
        || c == ';';
}

pair<CCGCat*,int> CCGCat::parseLeast(string &str, int start)
{
    pair<CCGCat*,int> firstRes;
    if(str[start] == '(')
    {
        firstRes = parseLeast(str,start+1);
        if(str[firstRes.second] != ')')
            throw CCGTypeError("Unmatched parenthesis: \""+str.substr(start,firstRes.second+1-start)+"\"");
        firstRes.second++;
    }
    else if(admissibleCharForType(str[start]))
    {
        int idx = start+1;
        while(idx < str.size() && admissibleCharForType(str[idx]))
            idx++;

        string baseType = str.substr(start,idx - start);
        string annotation = "";

        if(idx < str.size() && str[idx] == '[')
        {
            int annotationBegin = ++idx;
            while(islower(str[idx]) && isalpha(str[idx]))
                idx++;
            if(idx < str.size() && str[idx] != ']')
                throw CCGTypeError("Unmatched [ : \""+str.substr(start,idx+1-start)+"\"");

            annotation = str.substr(annotationBegin,idx-annotationBegin);
            idx++;
        }

        CCGLabel* firstCat = new CCGLabel(baseType,annotation);
        firstRes = make_pair(firstCat,idx);
    }

    int idx = firstRes.second;
    if(idx < str.size() && (str[idx] == '/' || str[idx] == '\\'))
    {
        bool right = (str[idx] == '/');
        
        pair<CCGCat*,int> res = parseLeast(str,idx+1);

        return make_pair(new CCGQuotient(firstRes.first,res.first, right),res.second);
    }
    else
        return firstRes;
}

CCGLabel::CCGLabel(string mainType, string annotation) :
    mainType(mainType),
    annotation(annotation)
{

}

string CCGLabel::toString(bool annotations) const
{
    if(annotation == "" || !annotations)
        return mainType;
    else
        return (mainType + "["+annotation+"]");
}

CCGQuotient::CCGQuotient(CCGCat* n, CCGCat* d, bool r) :
    num(n),
    denom(d),
    right(r)
{

}

string CCGQuotient::toString(bool annotations) const
{
    string first = num->toString(annotations), second = denom->toString(annotations);
    if(num->isQuotient())
        first = "(" + first + ")";
    if(denom->isQuotient())
        second = "(" + second + ")";

    if(right)
        return (first + "/" + second);
    else
        return (first + "\\" + second);
}

bool CCGLabel::isLabel() const
{
    return true;
}

bool CCGQuotient::isQuotient() const
{
    return true;
}

bool CCGQuotient::isLeft() const
{
    return !right;
}

bool CCGQuotient::isRight() const
{
    return right;
}

CCGQuotient::~CCGQuotient()
{
    delete num;
    delete denom;
}

