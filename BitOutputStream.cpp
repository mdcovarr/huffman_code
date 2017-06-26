//Michael Covarrubias
//PID#: A12409694
//Mahaela Johnson
//PID#: A09635628

#include <iostream>
#include <fstream>
#include "BitOutputStream.hpp"
using namespace std;

/** outputs the buffer to the output stream 
 */
void BitOutputStream::flush()
{
	out.put(buf);
	out.flush();
	buf = nbits = 0;
}

/** puts the specified bit into the buffer at the 
 * specified location
 */
void BitOutputStream::writeBit(int i)
{
	if (nbits == 8)
	{
		flush();
	}
	
	i = i & 1;
	buf = buf | (i << nbits);	
	nbits++;		
}
