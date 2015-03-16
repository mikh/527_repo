#include "hash.h"
#include <vector>
#include <iostream>
#include <ifstream>

#define P1_CODE
#define P2_CODE

const char START_CHAR = '!';
const char END_cHAR = '~';
const string P1_FILENAME = "p1_hashes.txt";
const string P2_FILENAME = "p2_hashes.txt";

const string P2_RAINBOW_TABLE = "table.txt";

using namespace std;

vector<string> load_hashes(string filename);
vector<string> brute_force(vector<string> hashes);
void print_hash_passwords(vector<string> hashes, vector<string> cracks);

int main(){
	cout<<"Starting Q4 code"<<endl;

	#ifdef P1_CODE
		vector<string> hash_data = load_hashes(P1_FILENAME);
		vector<string> cracks = brute_force(hash_data);
		print_hash_passwords(hash_data, cracks);
	#endif

	#ifdef P2_CODE
		vector<string> p2_hashes = load_hashes(P2_FILENAME);
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

vector<string> brute_force(vector<string> hashes){
	vector<string> passwords;
	vector<string> cracks;

	for(int ii = 0; ii < hashes.length(); ii++){
		bool found = false;
		string c_h = hashes[ii];
		for(char jj = START_CHAR; jj <= END_cHAR; jj++){
			for(char kk = START_CHAR; kk <= END_cHAR; kk++){
				for(char ll = START_CHAR; ll <= END_cHAR; ll++){
					string password = "";
					password += jj;
					password += kk;
					password += ll;
					string trial_hash = hash(password);
					if(trial_hash.compare(c_h) == 0){
						cracks.push_back(password);
						found = true;
						break;
					}
				}
				if(found)
					break;
			}
			if(found)
				break;
		}
		if(!found)
			cracks.push_back("NONE_FOUND");
	}
	return cracks;
}

void print_hash_passwords(vector<string> hashes, vector<string> cracks){
	for(int ii = 0; ii < hashes.size(); ii++){
		printf("%-45s -> %10s\n", hashes[ii], cracks[ii]);
	}
}

vector< pair<string, string>> load_rainbow_table(string rt_filename){
	cout<<"Loading rainbox table from file "<<filename<<endl;
	ifstream file(filename);
	string str;
	vector<string> lines;
	while(getline(file, str)){
		
	}
}