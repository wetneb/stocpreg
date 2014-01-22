

#include "ccg.h"

CCGTypeError::CCGTypeError(string what) : mWhat(what)
{

}

const char* CCGTypeError::what()
{
    return mWhat.c_str();
}

static CCGCat CCGCat::parse(string str)
{
    if(str.size() == 0)
        throw CCGTypeError("Unable to parse the empty string");

    pair<CCGCat,int> res = parseLeast(str,0);
    if(res.second == str.size())
        return res.first;
    else throw CCGTypeError("Trailing characters at the end of the type: \""+str.substr(res.second)+"\"");
}

static pair<CCGCat,int> CCGCat::parseLeast(string &str, int start)
{
    if(str[start] == '(')
    {
        pair<CCGCat,int> res = parseLeast(str,start+1);
        if(str[res.second] != ')')
            throw CCGTypeError("Unmatched parenthesis: \""+str.substr(start,res.second+1-start)+"\"");
        res.second++;
        return res;
    }
    else if(isupper(str[start]))
    {
        int idx = start+1;
        while(isupper(str[idx]))
            idx++;

        string baseType = str.substr(start,idx-1);
        string annotation = "";

        if(str[idx] == '[')
        {
            int annotationBegin = ++idx;
            while(islower(str[idx]))
                idx++;
            if(str[idx] != ']')
                throw CCGTypeError("Unmatched [ : \""+str.substr(start,idx+1-start)+"\"");

            annotation = str.substr(annotationBegin,idx-1);
            idx++;
        }

        CCGCat firstCat(baseType,annotation);
        if(str[idx] == '/' || str[idx] == '\\')
        {
            bool right = (str[idx] == '/');
            
            pair<CCGCat,int> res = parseLeast(str,idx+1);

            return make_pair(CCGQuotient(firstCat,res.first),res.second);
        }
        else
            return make_pair(firstCat,idx);
    }
}

CCGLabel::CCGLabel(string mainType, string annotation) :
    mainType(mainType),
    annotation(annotation)
{

}

string CCGLabel::toString()
{
    if(annotation == "")
        return mainType;
    else
        return (mainType + "["+annotation+"]");
}

CCGQuotient::CCGQuotient(CCGCat &num, CCGCat &denom, bool right)
    num(num),
    denom(denom),
    right(right)
{

}

string CCGQuotient::toString()
{
    string first = num.toString(), second = denom.toString();
    if(num.isQuotient())
        first = "(" + first + ")";
    if(denom.isQuotient())
        second = "(" + denom + ")";

    if(right)
        return (first + "/" + second);
    else
        return (first + "\\" + second);
}

bool CCGLabel::isLabel()
{
    return true;
}

bool CCGQuotient::isQuotient()
{
    return true;
}

bool CCGQuotient::isLeft()
{
    return !right;
}

bool CCGQuotient::isRight()
{
    return right;
}

