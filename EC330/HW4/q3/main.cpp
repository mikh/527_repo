#include <iostream>

#include "myBloomFilter.h"

using namespace std;

int main(){
	cout<<"Starting bloom filter functions"<<endl;
	MyBloomFilter *mbf = new MyBloomFilter(10);
	printf("%-10s exists? = %d\n", "hola", mbf->exists("hola"));
	mbf->insert("hola");
	mbf->insert("   asd");
	mbf->insert("232ad");
	printf("%-10s exists? = %d\n", "hola", mbf->exists("hola"));
	printf("%-10s exists? = %d\n", "232ad", mbf->exists("232ad"));
	printf("%-10s exists? = %d\n", "       dd", mbf->exists("       dd"));
	printf("%-10s exists? = %d\n", "aa", mbf->exists("aa"));
	mbf->print_statistics();

	cout<<mbf->output()<<endl;
	MyBloomFilter *mbf2 = new MyBloomFilter("10011001");
	cout<<mbf2->output()<<endl;
	return 0;

}