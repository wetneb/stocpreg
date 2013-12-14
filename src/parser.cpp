#include "parser.h"


/*********************************************/
/* TODO TODO TODO TODO TODO TODO ....... */
/* REMOVE ALL the as = as + … */
// it's inefficient


// Set up the parser for the following frame string
SPGParser::SPGParser(FrameString &fs)
{
    frame = fs;
	n = fs.size();

	assignments.resize(n);
    computed.resize(n);
	for(int i = 0; i < n; i++)
    {
	    assignments[i].resize(n);
        computed[i].resize(n, false);
    }

	widx.resize(n);

	for(int i = 0; i < n; i++)
	{
	    if(i == 0)
		widx[i] = 0;
	    else if(isLB(i))
		widx[i] = widx[i-1] + 1;
	    else widx[i] = widx[i-1];
	}

    // initialize headType
    headType.resize(n, -1);
    int curHeadType = -1;
    for(int i = 0; i < n; i++)
    {
        if(curHeadType == -1 && isType(i))
            curHeadType = i;
        else if(curHeadType != -1 && !isType(i))
            curHeadType = -1;
        headType[i] = curHeadType;
    }
}

// Run the parser and get the probability that the whole
// string is reductible.
float SPGParser::run()
{
    for(int i = 0; i < n; i++)
        cout << frame.getProba(i) << " ";
    cout << endl;
	
    if(!reductible(0, n-1))
        return 0.0;

    return proba(assignments[0][n-1]);
}

// Overloading + for set union
set<Assignment> operator+(const set<Assignment> &lhs, const set<Assignment> &rhs);

// Is there an assignment making the substring [i;j]
// reductible ?
bool SPGParser::reductible(int i, int j)
{
	if(i < 0 || i >= n || j < 0 || j >= n || i > j)
	    return false;
	if(computed[i][j])
	    return (assignments[i][j].size() > 0);

    string subframe = frame.toString(i,j);
	set<Assignment> result = computeReductible(i,j);
    
    cout << "["<<i<<"]["<<j<<"] : "<<result.size()<<" : "<<subframe <<endl;
    assignments[i][j] = result;
    computed[i][j] = true;

	return (result.size() > 0);
}

// Do actually the computation
set<Assignment> SPGParser::computeReductible(int i, int j)
{
    set<Assignment> as;

	// Base case
	if(i == j && isType(i) && isUnit(i))
    {
        as.insert(Assignment::singleton(headType[i]));
        return as;
    }

	if(j == i+1)
	{
		if(isType(i) && isType(j) && gcon(i,j))
        {
            as.insert(Assignment::singleton(headType[i]));
            // we could add j but headType[i] == headType[j] so it's no use
        }
		
       return as;
	}

    if(i == 21 && j == 26)
    {
        cout << "widx[j] = "<<widx[j]<<endl
            << "widx[i] = "<<widx[i]<<endl
            << "gcon(i,j) = "<<gcon(i,j)<<endl;
        cout << "at(i) = "<<at(i).toString()<<endl
            << "at(j)^l = "<<at(j).leftAdjoint().toString()<<endl
            << "i <= j^l = "<<(at(i) <= (at(j).leftAdjoint()))<<endl
            << "i.exp = "<<at(i).exponent<<endl
            << "j^l.exp = "<<at(j).leftAdjoint().exponent << endl
            << "n <= n = "<<Pregroup::less(at(j).leftAdjoint().baseType, at(i).baseType)<<endl;
    }

	if(isType(i) && isType(j) &&
		isStar(i+1) &&
		isStar(j-1) &&
		widx[j] == widx[i]+1 &&
		gcon(i,j))
	{
        Assignment a = Assignment::singleton(headType[i]);
        a.insert(headType[j]);
        as.insert(a);
        return as;
	}

	if(isType(i) && isType(j))
	{
		// A1a
		for(int k = i+1; k < j-1; k++)
		    if(isType(k) && reductible(i,k) && reductible(k+1,j))
                as = as + product(assignments[i][k], assignments[k+1][j]);

		// A1b
		for(int k = i+1; k < j-1; k++)
		    if(isRB(k) && isLB(k+1) && reductible(i,k) && reductible(k+1,j))
                as = as + product(assignments[i][k], assignments[k+1][j]);

		// A2
		if(gcon(i,j))
        {
            set<Assignment> a = assignments[i+1][j-1];
            Assignment rhs;
            rhs.insert(headType[i]);
            rhs.insert(headType[j]);
            set<Assignment> b;
            b.insert(rhs);
            as = as + product(a, b);
        }
	}

	// A3a
	if(isLB(i) && isType(j))
	{
		for(int k = i+1; k < j && widx[k] == widx[i]; k++)
		    if(isStar(k) && reductible(k+1, j))
                as = as + assignments[k+1][j];
	}

	// A3b
	if(isRB(j) && isType(i))
	{
		for(int k = j-1; k > i && widx[k] == widx[j]; k--)
		    if(isStar(k) && reductible(i,k-1))
                as = as + assignments[i][k-1];
	}
	
	// A4b
	if(isType(i) && isType(j) && isStar(j-1) && gcon(i,j)
		&& widx[i] != widx[j])
	{
		for(int k = j-1; k > i && widx[k] == widx[j]; k--)
		    if(isRB(k-1) && reductible(i+1,k-1))
                as = as + assignments[i+1][k-1];
	}

	// A4c
	if(isType(i) && isType(j) &&
	    isStar(i+1) && isStar(j-1) &&
	    1 + widx[i] < widx[j] &&
	    gcon(i,j))
	{
	    int k1, k2;
	    for(k1 = i+1; k1 < j && !isRB(k1); k1++);
	    for(k2 = j-1; k2 > i && !isLB(k2); k2--);
        if(reductible(k1,k2))
            as = as + assignments[k1][k2];
	}

	// A5
	if(isLB(i) && isRB(j))
	{
	    float totalProb = 0;
	    for(int k1 = i+1; k1 < j && !isRB(k1); k1++)
	    {
		if(isType(k1) && isStar(k1-1))
		{
		    for(int k2 = j-2; k2 > i && !isLB(k2); k2--)
		    {
                if(isType(k2) && isStar(k2+1) && reductible(k1,k2))
                    as = as + assignments[k1][k2];
		    }
		}
	    }
	}

	return as;
}

/// HELPERS

FrameElem* SPGParser::get(int pos)
{
	return frame[pos];	
}

SimpleType SPGParser::at(int pos)
{
    FrameElem* elem = get(pos);
	return (dynamic_cast<TypeElem*>(elem))->simpleType;
}

bool SPGParser::isType(int pos)
{
	return get(pos)->isType();
}

bool SPGParser::isLB(int pos)
{
	return get(pos)->isLB();	
}

bool SPGParser::isRB(int pos)
{
	return get(pos)->isRB();	
}

bool SPGParser::isStar(int pos)
{
	return get(pos)->isStar();	
}

bool SPGParser::isUnit(int pos)
{
	return (isType(pos) && at(pos).isUnit());
}

// Does the Generalized Contraction rule applies ?
bool SPGParser::gcon(int i, int j)
{
	return (isType(i) && isType(j) &&
		at(i).gcon(at(j)));
}

// What is the probability that this type has been assigned ?
float SPGParser::proba(int i)
{
	if(isType(i))
	    return frame.getProba(i);
	else
	    return -1.0;
}


//! What is the probability of this type assignment ?
float SPGParser::proba(Assignment a)
{
    float prob = 1.0;
    for(Assignment::iterator it = a.begin();
            it != a.end(); it++)
        prob *= proba(*it);
    return prob;
}

//! What is the probability of this set of type assignments ?
float SPGParser::proba(set<Assignment> s)
{
    float prob = 0.0;
    for(set<Assignment>::iterator it = s.begin();
            it != s.end(); it++)
        prob += proba(*it);
    return prob;
}

//! Do the product of two assignment sets :
// A x B = { a u b, a \in A, b \in B }
set<Assignment> SPGParser::product(const set<Assignment> &a, const set<Assignment> &b)
{
    set<Assignment> res;
    for(set<Assignment>::const_iterator ita = a.begin();
            ita != a.end(); ita++)
        for(set<Assignment>::const_iterator itb = b.begin();
                itb != b.end(); itb++)
            res.insert(ita->createUnion(*itb));

    return res;
}

//! Create a singleton
Assignment Assignment::singleton(int n)
{
    Assignment a;
    a.insert(n);
    return a;
}

//! Create the union with another set
Assignment Assignment::createUnion(const Assignment &rhs) const
{
    Assignment a(*this);

    for(Assignment::iterator it = rhs.begin();
            it != rhs.end(); it++)
        a.insert(*it);

    return a;
}

// Overloading + for set union
set<Assignment> operator+(const set<Assignment> &lhs, const set<Assignment> &rhs)
{
    set<Assignment> res(lhs);
    for(set<Assignment>::iterator it = rhs.begin();
            it != rhs.end(); it++)
        res.insert(*it);

    return res;
}

