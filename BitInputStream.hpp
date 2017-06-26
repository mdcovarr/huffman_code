//Michael Covarrubias
//PID#: A12409694
//Mahaela Johnson 
//PID#: A09635628


#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>
#include <fstream>
using namespace std;

class BitInputStream {
private:
	char buf;
	int nbits;
	istream & in;

public:
	BitInputStream(istream & is) : in(is)
	{
		buf = 0;
		nbits = 8;
	}	

	/** fills the buffer from the input stream
	*/
	void fill();
	
	/** reads the bits of the buffer one at a time
	*/
	int readBit();
};

#endif
