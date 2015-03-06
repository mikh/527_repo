#include "sha1.h"
#include "hash.h"

/**
 * converts a hex character into an integer
 * @param hex The hexadecimal character to convert 0-9,a-f (lower case)
 * @return an integer 0-15 representing the hex character
 */
int hexTOint(char hex) {
	if (hex>='0' && hex<='9')
		return hex - '0';
	else
		return 10+ hex - 'a';
}

/**
 * produce a hash of a given string
 * @param str The string we wish to hash.
 * @return A string of 40 hex characters corresponding to a hash of the string.
 */
string hash(string str) {
	unsigned char shaResult[20];
	char hexResult[41];
	sha1::calc(str.c_str(), str.length(), shaResult); // calculate the modified sha1 hash
	sha1::toHexString(shaResult,hexResult);           // convert the hash to a string
	
	return string(hexResult);
}

/**
 * produce a string of len characters (each between ! and ~) from the provided string
 * @param str The string to be reduced to len characters.
 * @param len The length of the reduced string.
 * @return A collection of len characters (each between ! and ~).
 *
 * @requires 0 < len <= 40.
 */
string reduce(string str, int len) {
	string temp = hash(str);
	string result(len,0);

	// divide the sha1 hash into len groups, each providing one character of the result
	for (int ii=0; ii<temp.length(); ii++)
		result[ii % len] = ((result[ii % len]) + hexTOint(temp[ii]))%94;
		
	// convert to characters ! though ~
	for (int ii=0; ii<result.length(); ii++)
		result[ii] += 0x21;
	
	return result;	
}
