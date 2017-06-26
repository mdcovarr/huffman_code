//Michael Covarrubias
//PID#: A12409694
//Mahaela Johnson
//PID#: A09635628
//Assignment 2

#include "HCNode.hpp"
#include "HCTree.hpp"

/** compares frequencies of HCNode's and returns the 
 *  one with the higher priority
 */
bool comp(HCNode* one, HCNode* other)
{
	return (one < other);
}

/** overloads the < operator in order to be able to correctly 
 *  compare the HCNodes
 */
bool HCNode::operator<(const HCNode& other)
{
	if (count != other.count)
	{
		if (count > other.count)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return symbol < other.symbol;
	}
}


