#include <string>
using namespace std;

/**
 * converts a hex character into an integer
 * @param hex The hexadecimal character to convert 0-9,a-f (lower case)
 * @return an integer 0-15 representing the hex character
 */
int hexTOint(char hex);

/**
 * produce a hash of a given string
 * @param str The string to hash
 * @return A collection of sixteen "readable" characters (! through ~) corresponding to this string.
 */
string hash(string str);

/**
 * produce a string of len characters (each between ! and ~) from the provided string
 * @param str The string to be reduced to len characters.
 * @param len The length of the reduced string.
 * @return A collection of len characters (each between ! and ~).
 *
 * @requires 0 < len <= 40.
 */
string reduce(string str, int len);
