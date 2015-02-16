#include "bigNumT.h"
#include <iostream>
#include <cstdio>
#include <list>
#include <deque>
#include <sys/time.h>
#include <sys/resource.h>



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
        struct rusage usage;
        struct timeval start, end;
        long rss_s, rss_e, ixrss_s, ixrss_e, idrss_s, idrss_e, isrss_s, isrss_e;

	bigNumT<vector<int> > foo("81172150");
        bigNumT<deque<int> > foo2("81172150");
        bigNumT<list<int> > foo3("81172150");
	cout<<"vector"<<endl;

        getrusage(RUSAGE_SELF, &usage);
        start = usage.ru_stime;
        rss_s = usage.ru_maxrss;
        ixrss_s = usage.ru_ixrss;
        idrss_s = usage.ru_idrss;
        isrss_s = usage.ru_isrss;
        bigNumT<vector<int> > result = CollatzCount(foo);
        getrusage(RUSAGE_SELF, &usage);
        end = usage.ru_stime;
        rss_e = usage.ru_maxrss;
        ixrss_e = usage.ru_ixrss;
        idrss_e = usage.ru_idrss;
        isrss_e = usage.ru_isrss;

	cout << result.print() << endl;

        cout<<(end.tv_sec*1000000+end.tv_usec) - (start.tv_sec*1000000+start.tv_usec)<<endl;
        cout<<rss_e - rss_s<<endl;
        cout<<ixrss_e - ixrss_s <<endl;
        cout<<idrss_e - idrss_s << endl;
        cout<<isrss_e - isrss_s << endl;

        cout<<endl<<endl<<"deque"<<endl;

         getrusage(RUSAGE_SELF, &usage);
        start = usage.ru_stime;
        rss_s = usage.ru_maxrss;
        ixrss_s = usage.ru_ixrss;
        idrss_s = usage.ru_idrss;
        isrss_s = usage.ru_isrss;
        bigNumT<deque<int> > result2 = CollatzCount(foo2);
        getrusage(RUSAGE_SELF, &usage);
        end = usage.ru_stime;
        rss_e = usage.ru_maxrss;
        ixrss_e = usage.ru_ixrss;
        idrss_e = usage.ru_idrss;
        isrss_e = usage.ru_isrss;

        cout << result2.print() << endl;

        cout<<(end.tv_sec*1000000+end.tv_usec) - (start.tv_sec*1000000+start.tv_usec)<<endl;
        cout<<rss_e - rss_s<<endl;
        cout<<ixrss_e - ixrss_s <<endl;
        cout<<idrss_e - idrss_s << endl;
        cout<<isrss_e - isrss_s << endl;

                cout<<endl<<endl<<"list"<<endl;

         getrusage(RUSAGE_SELF, &usage);
        start = usage.ru_stime;
        rss_s = usage.ru_maxrss;
        ixrss_s = usage.ru_ixrss;
        idrss_s = usage.ru_idrss;
        isrss_s = usage.ru_isrss;
        bigNumT<list<int> > result3 = CollatzCount(foo3);
        getrusage(RUSAGE_SELF, &usage);
        end = usage.ru_stime;
        rss_e = usage.ru_maxrss;
        ixrss_e = usage.ru_ixrss;
        idrss_e = usage.ru_idrss;
        isrss_e = usage.ru_isrss;

        cout << result3.print() << endl;

        cout<<(end.tv_sec*1000000+end.tv_usec) - (start.tv_sec*1000000+start.tv_usec)<<endl;
        cout<<rss_e - rss_s<<endl;
        cout<<ixrss_e - ixrss_s <<endl;
        cout<<idrss_e - idrss_s << endl;
        cout<<isrss_e - isrss_s << endl;
}


/*
vector<int>
deque<int>
list<int>


vector<int>
+ O(n)
* O(n^2)












*/