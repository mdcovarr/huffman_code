//Michael Covarrubias
//PID#: A12409694
//Mahaela Johnson 
//PID#: A09635628


#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>
#include <fstream>

using namespace std;

class BitOutputStream {
private:
	char buf;
	int nbits;
	ostream & out;
public:
	BitOutputStream(ostream & os) : out(os), buf(0), nbits(0) {
	}
	
	/** outputs the buffer into the output stream
 	*/
	void flush();
	
	/** writes the a specified bit into the buffer at the
	* appropriate location
	*/
	void writeBit(int i);	
};

#endif
