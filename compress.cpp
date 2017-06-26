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
using namespace std;

int main(int argc, char*  argv[])
{

	//check for correct number of arguements
	if (argc != 3)
	{
		cout << "Invalid number of arguments. " << endl;
		cout << "Usage: ./compress <input filename> <output filename>";
		cout << endl;
		return -1;
	}
	
	ifstream in;
	ofstream out;
	in.open(argv[1], ios::binary);
	out.open(argv[2], ios::binary);

	//check that file is open
	if(!in.is_open())
	{
		cout << "Invalid input file. No file was opened. ";
		cout << "Please try again " << endl;
		return -1;
	}

	//check if file is empty
	in.seekg(0, ios_base::end);
	unsigned int len = in.tellg();
	if (len == 0)
	{
		cout << "The input file is empty. " << endl;
		return -1;
	}
	in.seekg(0, ios_base::beg);
	
	vector<int> freqs(256, 0);
	unsigned char nextChar;
	unsigned int count = 0;
	
	//read the characters in the file and assign their frequency
	//to freqs
	while (1)
	{
		nextChar = in.get();
		if (in.eof())
		{
			break;
		}
		freqs[nextChar] = freqs[nextChar] + 1;
		count++;	
	}

	//write the number lines in the header
	int numSymb =0;
	for(int i = 0;i < 256; ++i)
	{
		if(freqs[i] > 0)
		{
			numSymb++;
		}
	}
	out<<numSymb<<endl;	
	
	//write the header
	for (int i = 0; i < 256; i++)
	{
		int size = 3;
		if(freqs[i] >0)	{
			if(i<100){
				int size = 2;
				out.put('0');
				if(i<10) {
					int size =1;
					out.put('0');
				}		
			}
			
			out<< i << freqs[i]<<endl;
		}
	}	

	//make a tree
	HCTree* tree = new HCTree();
	tree->build(freqs);
	BitOutputStream* outStream = new BitOutputStream(out);
	in.close();
	in.open(argv[1], ios::binary);
	
	//compress the file
	while(1)
	{
		nextChar = in.get();
		if (in.eof())
		{
			break;
		}
		tree->encode((byte)nextChar, *outStream);
	}
	outStream->flush();
	
	//delete objects and close files
	delete tree;	
	delete outStream;
		
	if(in.is_open())
	{
		in.close();
	}
	if(out.is_open())
	{
		out.close();
	}
	return 0;	
}


