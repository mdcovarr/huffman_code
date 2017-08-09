//Michael Covarrubias
//PID#: A12409694
//Mahaela Johnson 
//PID#: A09635628


#ifndef HCNODE_HPP
#define HCNODE_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
class HCNode {
  friend bool comp(HCNode* one, HCNode* other);

public:
  int count;
  byte symbol; // byte in the file we're keeping track of
  HCNode* c0;  // pointer to '0' child
  HCNode* c1;  // pointer to '1' child
  HCNode* p;   // pointer to parent

  /** Constructor for HCNode class in order to keep track 
   *  of nodes initialized with given symbols
   */
  HCNode(int count,
	 byte symbol,
	 HCNode* c0 = 0,
	 HCNode* c1 = 0,
	 HCNode* p = 0)
    : count(count), symbol(symbol), c0(c0), c1(c1), p(p) { }

  /** Less-than comparison, so HCNodes will work in std::priority_queue
   *  We want small counts to have high priority.
   *  And we want to break ties deterministically.
   */
  bool operator<(const HCNode& other);
};

/** For printing an HCNode to an ostream
 *  useful for debugging.
 */
ostream& operator<<(ostream&, const HCNode&) __attribute__((weak)); // shut the linker up
ostream& operator<<(ostream& stm, const HCNode& n) {
    stm << "[" << n.count << "," << (int) (n.symbol) << "]";
    return stm;
}

bool comp(HCNode* one, HCNode* other);


#endif // HCNODE_HPP
