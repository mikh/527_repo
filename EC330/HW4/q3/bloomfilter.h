#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H
#include <string>
using namespace std;

class BloomFilter{
public:
	/**
	* Instantiate an empty Bloom filter of length chars
	*/
	BloomFilter (int mm) : length(mm) {}

	/**
	* Instantiate a Bloom filter from a given string
	* @requires must have been produces by the output() call of a BloomFilter object
	*/
	BloomFilter (string filter) : length(filter.length()) {}

	/**
	* Inserts into the filter
	*/
	void insert(string item);

	/**
	* Checks whether is in the filter
	* @return  true if the item is probably in the filter
	*          false if the item is definitely not in the filter
	*/
	bool exists(string item);

	/**
	* @return A string of characters representing the Bloom filter
	*/
	string output();

protected:
	int length;	/** The length of the Bloom filter, in chars */
};

#endif /* BLOOMFILTER_H */