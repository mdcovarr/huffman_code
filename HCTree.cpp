//Michael Covarrubias
//PID#: A12409694
//Mahaela Johnson 
//PID#: A09635628

#include "HCTree.hpp"
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
	
using namespace std;

/** build the Huffman tree, where all the leaf nodes are the different 
 *  byte instances in the input file
 */	
void HCTree::build(const vector<int>& freqs)
{

	
	priority_queue<HCNode*,vector<HCNode*>,HCNodePtrComp> pq;
	unsigned int size = freqs.size();
	HCNode* node1;
	HCNode* node2;

	// create HCNodes for all frequencies of bytes that are not 0
	for (int i = 0; i < size; i++)
	{
		if (freqs[i] != 0)
		{
			
			HCNode* p = new HCNode(freqs[i], i, 0, 0, 0);
			leaves[i] = p;
			pq.push(p);
		}
	}

	// we keep combining subtrees until we have one huffman tree	
	while (pq.size() != 1)
	{
		node1 = pq.top();
		pq.pop();
		node2 = pq.top();
		pq.pop();
		
		HCNode* parent = new HCNode(node1->count+node2->count, node1->symbol, node1, node2, 0);
		node1->p = parent;
		node2->p = parent;
		pq.push(parent);
		
	}
	
	//set the root to the root of the huffman tree	
	root = pq.top();
	pq.pop();
		
}

/** using the huffman tree, we encode sequences of bits into the outstream 
 *  depending on the specified sequence needed to reace the specified byte 
 *  symbol
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const
{
	HCNode* curr;
	curr = leaves[symbol];
	vector<int> vec;

	//encode 0 if there is only one distinced byte in an input file
	if (curr == root)
	{

		vec.push_back(0);
	}
	
	//while we have not reached the root we keep iterating up the tree
	//in order to get specified bit encoding sequence
	while (curr->p != NULL)
	{
		if (curr == curr->p->c1)
		{
			vec.push_back(1);
		}
		else
		{
			vec.push_back(0);
		}
		curr = curr->p;		
	}

	//successfully reverse the bit sequence	
	for(int i = vec.size() - 1; i >= 0; i--)
	{
		
		out.writeBit(vec[i]);
	}
	
}

/** using the huffman tree we output the '1' and '0' ascii characters 
 *  to the outfile depending on the special sequence needed to get 
 *  to the leave node of the specified byte symbol
 */
void HCTree::encode(byte symbol, ofstream& out) const
{
	HCNode* curr;
	curr = leaves[symbol];
	unsigned char outChar;
	vector<char> vec;

	//encoding 0 ascii character if there is only one distinct byte 
	//symbol
	if (curr == root)
	{
		outChar = '0';
		vec.push_back(outChar);
	}
	
	//starting at the leaf, while we have not reached the root, we continue
	//iterating in order to get the specified encoding sequence of a 
	//specified byte symbol	
	while (curr->p != NULL)
	{
		if(curr == curr->p->c1)
		{
			outChar = '1';
			vec.push_back(outChar);
		}
		else
		{
			outChar = '0';
			vec.push_back(outChar);
		}
		curr = curr->p;
	}

	
	//successfully reverse the bits sequence in order to get the correct
	//specified bit sequence in order to get to special symbol's leaf node
	//from the root	
	for(int i = vec.size() - 1; i >= 0; i--)
	{
		outChar = vec[i];
		out.put(outChar);
	}
	

}

/** goes throught the built huffman tree in order to decode the encrypted 
 *  bit sequence of the input file to determine the encoded specified byte 
 *  symbol
 */ 
int HCTree::decode(BitInputStream& in) const
{
	HCNode* curr = root;
	int val;

	//while we have not iterated down to a leaf node, we continue iterating
	//down the huffman tree in order to get the specified symbol	
	while(1)
	{
		val = in.readBit();
		if (curr == root && curr->c0 == NULL && curr->c1 == NULL)
		{
			return curr->symbol;	
		}
		if (val == 1)
		{
			curr = curr->c1;
		}
		else
		{
			curr = curr->c0;
		}
		
		
		if (curr->c0 == NULL && curr->c1 == NULL)
		{
			break;
		}
	}
	return curr->symbol;
}

/** goes through the buit huffman tree in order to determine which 
 *  special byte symbol was encoded by the '1' and '0' ascii characters
 *  in the input file
 */ 
int HCTree::decode(ifstream& in) const
{
	unsigned char nextChar;
	HCNode* curr = root;

	//while we have not iterated down to a leaf node we continue iterating
	//down the huffman tree in order to get the specified symbol	
	while(1)
	{
		nextChar = in.get();
		if (in.eof())
		{
			return 0;
		}
		if (curr == root && curr->c0 == NULL && curr->c1 == NULL)
		{
			return curr->symbol;
		}
		
		if (nextChar == '1')
		{
			curr = curr->c1;	
		}
		else
		{
			curr = curr->c0;
		}
		
		if ( curr->c0 == NULL && curr->c1 == NULL)
		{
			break;	
		}
	}
	return curr->symbol;
	
}

/** helper function used to delete all nodes of the bulit huffman tree
 *  in a post order traversal 
 */
void HCTree::deleteAllNodes(HCNode* n)
{
	if (n == NULL)
	{
		return;
	}

	//recursively deletes the left subtree	
	if (n->c0 != NULL)
	{
		deleteAllNodes(n->c0);
	}

	//recursively deletes the right subtree
	if (n->c1 != NULL)
	{
		deleteAllNodes(n->c1);
	}
	
	delete n;
}
