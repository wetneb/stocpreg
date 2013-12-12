#include "parser.h"

// Set up the parser for the following frame string
SPGParser::SPGParser(FrameString fs) :
    frame(fs)
{
	n = frame.size();

	redProba.resize(n);
	for(int i = 0; i < n; i++)
	    redProba[i].resize(n, -1.0);

	widx.resize(n);

	for(int i = 0; i < n; i++)
	{
	    if(i == 0)
		widx[i] = 0;
	    else if(isLB(i))
		widx[i] = widx[i-1] + 1;
	    else widx[i] = widx[i-1];
	}
}

// Run the parser and get the probability that the whole
// string is reductible.
float SPGParser::run()
{
	return reductible(0, n-1);
}

// Compute the probability that the substring [i;j] is
// reductible
float SPGParser::reductible(int i, int j)
{
	if(i < 0 || i >= n || j < 0 || j >= n || i > j)
	    return 0;
	if(redProba[i][j] >= 0)
	    return redProba[i][j];

	float result = computeReductible(i,j);
	redProba[i][j] = result;
	return result;
}

// Do actually the computation
float SPGParser::computeReductible(int i, int j)
{
	// Base case
	if(i == j && isType(i) && isUnit(i))
	    return proba(i);

	if(j == i+1)
	{
		if(isType(i) && isType(j) && gcon(i,j))
		    return proba(i) * proba(j);
		else
		    return 0;
	}

	if(isType(i) && isType(j) &&
		isStar(i+1) &&
		isStar(j-1) &&
		widx[j] == widx[i]+1 &&
		gcon(i,j))
	{
	    return proba(i)*proba(j);
	}

	if(isType(i) && isType(j))
	{
		float totalProb = 0;

		// A1a
		for(int k = i+1; k < j-1; k++)
		    if(isType(k))
			totalProb += reductible(i,k)*reductible(k+1,j);

		//////////////////////////////////////////////////
		// TODO check that A1a, A1b and A2 are disjoint //
		//////////////////////////////////////////////////
	
		// A1b
		for(int k = i+1; k < j-1; k++)
		    if(isRB(k) && isLB(k+1))
			totalProb += reductible(i,k)*reductible(k+1,j);

		// A2
		if(gcon(i,j))
		    totalProb += reductible(i+1,j-1)*proba(i)*proba(j);
		return totalProb;
	}

	// A3a
	if(isLB(i) && isType(j))
	{
		for(int k = i+1; k < j && widx[k] == widx[i]; k++)
		    if(isStar(k))
			return reductible(k+1,j);
	}

	// A3b
	if(isRB(j) && isType(i))
	{
		for(int k = j-1; k > i && widx[k] == widx[j]; k--)
		    if(isStar(k))
			return reductible(k+1,j-1);
	}
	
	// A4b
	if(isType(i) && isType(j) && isStar(j-1) && gcon(i,j)
		&& widx[i] != widx[j])
	{
		for(int k = j-1; k > i && widx[k] == widx[j]; k--)
		    if(isRB(k-1))
			return reductible(i+1,k-1);
	}

	// A4c
	if(istype(i) && isType(j) &&
	    isStar(i+1) && isStar(j-1) &&
	    1 + widx[i] < widx[j] &&
	    gcon(i,j))
	{
	    int k1, k2;
	    for(k1 = i+1; k1 < j && !isRB(k1); k1++);
	    for(k2 = j-1; k2 > i && !isLB(k2); k2--);
	   	return reductible(k1,k2);
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
			totalProb += reductible(k1,k2);
		    }
		}
	    }
	    return totalProb;
	}

	// otherwise...
	return 0.0;
}

/// HELPERS

FrameElem SPGParser::get(int pos)
{
	return frame[pos];	
}

SimpleType SPGParser::at(int pos)
{
	return ((TypeElem)get(pos)).simpleType;
}

bool SPGParser::isType(int pos)
{
	return get(pos).isType();
}

bool SPGParser::isLB(int pos)
{
	return get(pos).isLB();	
}

bool SPGParser::isRB(int pos)
{
	return get(pos).isRB();	
}

bool SPGParser::isStar(int pos)
{
	return get(pos).isStar();	
}

bool SPGParser::isUnit(int pos)
{
	return get(pos).isUnit();
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

