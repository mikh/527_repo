#include "bigNumT.h"
#include <iostream>
#include <cstdio>
#include <list>


using namespace std;

/**
* @requires  >= 1
* @param nn The starting parameter.
* @return The number of Collatz calls needed to reach 1 from the parameter .
*         This implementation is iterative to avoid stack overflows
*/
template <typename T>
T CollatzCount(T nn) {
        T ONE("1");   T TWO("2");   T THREE("3");
        
        T result("1");
        for (;!(nn==ONE);result=result+ONE) {	//addition
                if (TWO*(nn/TWO)==nn) // i.e. nn is even	//multiplication, division, comparison
                nn = nn/TWO;	//assignment and division
                else                  // i.e. nn is odd
                nn = THREE*nn+ONE;	//multiplication and addition
        }
        return result;
}

int main(){
	bigNumT<list<int> > foo("81172150");
	bigNumT<list<int> > result = CollatzCount(foo);
	cout << result.print() << endl;
}


/*
vector<int>
deque<int>
list<int>


vector<int>
+ O(n)
* O(n^2)












*/