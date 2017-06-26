//Michael Covarrubias
//PID#: A12409694
//Mahaela Johnson
//PID#: A09635628

#include <iostream>
#include "BitInputStream.hpp"
using namespace std;

/** fills the buffer from the input stream
 */
void BitInputStream::fill()
{
	buf = in.get();
	nbits = 0;
	
}

/** reads the bits in the buffer one at a time and returns the 
 *  bit value
 */
int BitInputStream::readBit()
{
	if (nbits == 8)
	{
		fill();
	}
	
	
	int i = buf & (1 << nbits);
	i = i >> nbits;
	nbits++;
	return i;
}
