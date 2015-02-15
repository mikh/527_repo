#include "bigNumT.h"
#include "3a.h"
#include <iostream>
#include <cstdio>


using namespace std;

int main(){
	bigNumTwithMinus<> foo("3145234534");
	bigNumTwithMinus<> bar("1324532343");
	bigNumTwithMinus<> answer = foo - bar;
	cout << answer.print() << endl;
}