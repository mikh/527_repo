#include "hash.h"
#include <vector>
#include <iostream>
#include <ifstream>

#define P1_CODE

const string P1_FILENAME = "p1_hashes.txt";

using namespace std;

vector<string> load_hashes(string filename);

int main(){
	cout<<"Starting Q4 code"<<endl;

	#ifdef P1_CODE
		vector<string> hash_data = load_hashes(P1_FILENAME);
	#endif


	cout<<"Q4 code finished"<<endl;
	return 0;
}


vector<string> load_hashes(string filename){
	cout<<"Loading hashes from file "<<filename<<endl;
	ifstream file(filename);
	string str;
	vector<string> lines;

	while(getline(file, str)){
		lines.push_back(str);
	}

	return lines;
}

vector<string> brute_force(vector<string> hashes, int password_length){
	vector<string> passwords;
	for(int ii = 0; ii < hashes.length(); ii++){
		string c_h = hashes[ii];
		
	}
}