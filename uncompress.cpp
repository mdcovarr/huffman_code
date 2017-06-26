//Michael Covarrubias
//PID#: A12409694
//Mahaela Johnson
//PID#: A09635628

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitOutputStream.hpp"
#include "BitInputStream.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
	//check for the correct number of arguments
	if (argc != 3)
	{
		cout << "Invalid number of arguments. " << endl;
		cout << "Usage: ./unncompress <input filename> <output filename>";
		cout << endl;
		return -1;
	}

	ifstream in;
	ofstream out;
	in.open(argv[1], ios::binary);
	out.open(argv[2], ios::binary);

	//check if file is open
	if (!in.is_open())
	{
		cout << "Invalid input file. No file was opened. ";
		cout << "Please try again " << endl;
		return -1;
	}

	in.seekg(0, ios_base::end);
	unsigned int len = in.tellg();

	//check if file is empty
	if (len == 0)
	{
		cout << "The input file is empty. " << endl;
		return -1;
	}

	in.seekg(0, ios_base::beg);
	vector<int> freqs(256, 0);
	unsigned char nextChar;
	string str;
	int count = 0;
	int totcount = 0;
	int numSymb = 0; 
	int asciiSymb = 0;
	getline(in, str);
	numSymb = atoi(str.c_str());

	//read the header
	for(int i = 0; i < numSymb; ++i)
	{	
		char asciiNum[3];
		for(int j =0; j < 3; ++j)
		{
			asciiNum[j] = in.get();
		}
		string asciiStr(asciiNum);
		asciiSymb = atoi(asciiStr.c_str());
		getline(in, str);
		count = atoi(str.c_str());
		freqs[asciiSymb] = count;
		totcount += count;
		
	} 

	//build tree
	HCTree* tree = new HCTree();
	tree->build(freqs);
	
	BitInputStream* inStream = new BitInputStream(in);
	
	char outChar;
	
	//uncompress tree
	for (int j = 0; j < totcount; j++)
	{
		
		outChar = tree->decode(*inStream);	
		
		if (in.eof())
		{
			break;
		}
			
		out.put(outChar);
	}

	//delete objects and close file	
	delete tree;
	delete inStream;

	if (in.is_open())
	{
		in.close();
	}
	if (out.is_open())
	{
		out.close();
	}
	return 0;			
}
