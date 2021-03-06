#include "hash.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
//#include <pair>

//#define P1_CODE
//#define P2_CODE
#define P3_CODE

const char START_CHAR = '!';
const char END_CHAR = '~';
const string P1_FILENAME = "p1_hashes.txt";
const string P2_FILENAME = "p2_hashes.txt";
const int MAX_ITERATIONS = 500000;
const int P2_LENGTH = 5;

const string P2_RAINBOW_TABLE = "table.txt";
const string P3_RAINBOW_TABLE = "p3_rainbow_table.txt";

using namespace std;

vector<string> load_hashes(string filename);
vector<string> brute_force(vector<string> hashes);
void print_hash_passwords(vector<string> hashes, vector<string> cracks);
vector< pair<string, string> > load_rainbow_table(string rt_filename, int entry_length);
void print_rainbow_table(vector<pair<string, string> > table);
vector<string> rainbow_force(vector<string> hashes, vector<pair<string,string> > table, int max_iterations, int length);
vector<string> brute_force_5(vector<string> hashes);
string convert_to_string(long value, char start, char end, int length);
vector<pair<string,string> > build_rainbow_table(int length, char start, char end, int depth);
void write_rainbow_table_to_file(vector<pair<string,string> > rb_table, string filename);

int main(){
	cout<<"Starting Q4 code"<<endl;

	#ifdef P1_CODE
		vector<string> hash_data = load_hashes(P1_FILENAME);
		vector<string> cracks = brute_force(hash_data);
		print_hash_passwords(hash_data, cracks);
	#endif

	#ifdef P2_CODE
		vector<string> p2_hashes = load_hashes(P2_FILENAME);
		vector<pair<string, string> > p2_rainbow = load_rainbow_table(P2_RAINBOW_TABLE, P2_LENGTH);
		//print_rainbow_table(p2_rainbow);
		//vector<string> p2_cracks = rainbow_force(p2_hashes, p2_rainbow, MAX_ITERATIONS, P2_LENGTH);
		vector<string> p2_cracks = brute_force_5(p2_hashes);
		print_hash_passwords(p2_hashes, p2_cracks);
	#endif

	#ifdef P3_CODE
		vector<pair<string,string> > p3_rainbow = build_rainbow_table(5, START_CHAR, END_CHAR, 500000);
		write_rainbow_table_to_file(p3_rainbow, P3_RAINBOW_TABLE);
	#endif


	cout<<"Q4 code finished"<<endl;
	return 0;
}

string convert_to_string(long value, char start, char end, int length){
	//6786839 to base 32
	//23 - 24 - 3 -15 - 6

	int base = end - start + 1;

	string con = "";
	while(value > base){
		int part = value % base;
		con += (char)(start + part);
		value -= part;
		value /= base;
	}
	con += (char)(start + value);

	string r_con = "";
	for(int ii = con.length() - 1; ii >= 0; ii--)
		r_con += con[ii];
	for(int ii = r_con.length(); ii < length; ii++)
		r_con += start;

	return r_con;
}

void write_rainbow_table_to_file(vector<pair<string,string> > rb_table, string filename){
	
	ofstream file;
	file.open(filename.c_str());
	for(int ii = 0; ii < rb_table.size(); ii++){
		file<<"(   "<<rb_table[ii].first<<"  ,  "<<rb_table[ii].second<<"   )\n";
	}
	file.close();
}

vector<pair<string,string> > build_rainbow_table(int length, char start, char end, int depth){
	int distance = end - start + 1;
	double password_count = pow((double) distance, (double) length);

	double number_of_passwords = floor(password_count/depth);

	vector<pair<string, string> > rb_table;

	//depending on the hash and reduce functions, the distribution of hashed-reduced should be initialized differently
	//if the hashes are random enough, you will avoid collisions - which would make an entry in the rainbow table the same as another one


	double password_value = 0;
	for(double ii = 0; ii < number_of_passwords; ii++){
		string first_entry = convert_to_string(password_value, start, end, length);
		string h, r;
		r = first_entry;
		for(int jj = 0; jj < depth; jj++){
			h = hash(r);
			r = reduce(h, length);
		}
		string second_entry = r;

		pair<string, string> entry;
		entry.first = first_entry;
		entry.second = second_entry;
		rb_table.push_back(entry);
	}

	return rb_table;
}

vector<string> load_hashes(string filename){
	cout<<endl<<"Loading hashes from file "<<filename<<endl;
	ifstream file(filename.c_str());
	string str;
	vector<string> lines;

	while(getline(file, str)){
		lines.push_back(str);
		printf("%s\n", str.c_str());
	}
	cout<<"fully loaded"<<endl<<endl;
	return lines;
}

vector<string> brute_force(vector<string> hashes){
	cout<<endl<<"Performing brute force crack"<<endl;
	vector<string> passwords;
	vector<string> cracks;

	for(int ii = 0; ii < hashes.size(); ii++){
		bool found = false;
		string c_h = hashes[ii];
		for(char jj = START_CHAR; jj <= END_CHAR; jj++){
			for(char kk = START_CHAR; kk <= END_CHAR; kk++){
				for(char ll = START_CHAR; ll <= END_CHAR; ll++){
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
	cout<<"crack complete"<<endl<<endl;
	return cracks;
}

vector<string> brute_force_5(vector<string> hashes){
	cout<<"Starting brute force crack for length 5 passwords"<<endl;
	vector<string> cracks;
	for(int ii = 0; ii < hashes.size(); ii++)
		cracks.push_back("NONE_FOUND");

	int distance = END_CHAR - START_CHAR + 1;
	printf("%d\n", distance);
	double total_iters = (float)distance*(float)distance*(float)distance*(float)distance*(float)distance;
	double current_iteration = 0;
	double percentage = total_iters / 10000, percentage_val = percentage;
	printf("%f %f %f\n", total_iters, percentage, percentage_val);
	for(char a = START_CHAR; a <= END_CHAR; a++){
		for(char b = START_CHAR; b <= END_CHAR; b++){
			for(char c = START_CHAR; c <= END_CHAR; c++){
				for(char d = START_CHAR; d <= END_CHAR; d++){
					for(char e = START_CHAR; e <= END_CHAR; e++){
						current_iteration++;
						if((long)current_iteration == (long)percentage_val){
							printf("%.2f%% done. \n", (float)((long)percentage_val/(long)percentage)/100.0);
							percentage_val += percentage;
						}
						string out = "";
						out += a;
						out += b;
						out += c;
						out += d;
						out += e;
						string trial_hash = hash(out);
						for(int ii = 0; ii < hashes.size(); ii++){
							if(trial_hash.compare(hashes[ii]) == 0){
								cracks[ii] = out;
							}
						}
					}
				}
			}
		}
	}

	return cracks;
}

vector<string> rainbow_force(vector<string> hashes, vector<pair<string,string> > table, int max_iterations, int length){
	cout<<endl<<"Starting rainbow table crack"<<endl;
	vector<string> cracks;
	for(int ii = 0; ii < hashes.size(); ii++){
		string h = hashes[ii];
		int index = -1;
		for(int jj = 0; jj < max_iterations; jj++){
			string r = reduce(h, length);
			for(int kk = 0; kk < table.size(); kk++){

				if(table[kk].second.compare(r) == 0){
					index = kk;
					break;
				}
			}
			if(index != -1)
				break;
			h = hash(r);
		}
		if(index == -1)
			cracks.push_back("NONE_FOUND");
		else{
			string r = table[index].first;
			string h_r = hash(r);
			while(h_r.compare(h) != 0){
				r = reduce(h_r, length);
				h_r = hash(r);
			}
			cracks.push_back(r);
		}
	}
	cout<<"crack complete"<<endl<<endl;
	return cracks;
}

void print_hash_passwords(vector<string> hashes, vector<string> cracks){
	cout<<endl<<"Printing solutions"<<endl;
	for(int ii = 0; ii < hashes.size(); ii++){
		printf("%-45s -> %10s\n", hashes[ii].c_str(), cracks[ii].c_str());
	}
}

vector< pair<string, string> > load_rainbow_table(string rt_filename, int entry_length){
	cout<<"Loading rainbox table from file "<<rt_filename<<endl;
	vector< pair<string, string> > rb_table;
	ifstream file(rt_filename.c_str());
	string str;
	while(getline(file, str)){
		int index = 0;
		for(index; index < str.length(); index++){
			if(str[index] == '(')
				break;
		}
		index++;
		string first_entry = "";
		for(index; index < str.length(); index++){
			if(str[index] != ' ')
				break;
		}
		for(int ii = 0; ii < entry_length; ii++)
			first_entry += str[index++];
		for(index; index < str.length(); index++)
			if(str[index] == ',')
				break;
		index++;
		for(index; index < str.length(); index++)
			if(str[index] != ' ')
				break;
		string second_entry = "";
		for(int ii = 0; ii < entry_length; ii++)
			second_entry += str[index++];
		pair<string, string> new_entry;
		new_entry.first = first_entry;
		new_entry.second = second_entry;
		rb_table.push_back(new_entry);
	}

	return rb_table;
}


void print_rainbow_table(vector<pair<string, string> > table){
	for(int ii = 0; ii < table.size(); ii++){
		printf("%s - %s  -> %d - %d\n", table[ii].first.c_str(), table[ii].second.c_str(), table[ii].first.length(), table[ii].second.length());

	}
}
