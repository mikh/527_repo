#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string sequence(string input_file, int read_version);
void read_in_sequence(string input_file, vector<string> &strs, int read_version);
void print_list(vector<string> &list);
void print_list(vector<int> &list);
string construct_sequence(vector<string> &seq, vector<int> &pos);
int match_phrase(string intial, string input, int &pos)

const char blank_char = '&';

int main(void){
	printf("Solving Problem 4\n");

	string result = sequence("input_World_Wide_Web.txt", 0);
	printf("Output = %s\n", result.c_str());
	result = sequence("reads1.txt", 1);
	printf("Output = %s\n", result.c_str());
	printf("Done\n");
	return 0;
}

string sequence(string input_file, int read_version){
	vector<string> input, new_input;
	read_in_sequence(input_file, input, read_version);

	while(input.size() > 1){
		string phrase = input[0];
		input.erase(input.begin());
		int best_intensity = 0, best_phrase = "", best_position = 0;
		for(int ii = 0; ii < input.size(); ii++){
			int cur_position, cur_intensity;
			cur_intensity = match_phrase(phrase, input[ii], cur_position);
			if(cur_intensity > best_intensity){
				best_intensity = cur_intensity;
				best_position = cur_position;
				best_phrase = input[ii];
			}
		}
		if(best_intensity > 0){

		}
	}
}

string combine_strings(string phrase, string input, int position){
	string combined = "";
	if(position < input.length()){
		for(int ii = 0; ii < input.length()-position-1; ii++){

		}
	}
}

string sequence(string input_file, int read_version){
	vector<string> input;
	
	vector<string> sequence;
	vector<int> position;
	read_in_sequence(input_file, input, read_version);
	print_list(input);
	printf("\n\n");

	if(input.size() > 0){
		char temp;
		sequence.push_back(input[0]);
		position.push_back(0);
		input.erase(input.begin());
				string temp_output = construct_sequence(sequence, position);
				printf("%s  -  %s\n",phrase.c_str(), temp_output.c_str());

		while(input.size() > 0){
			for(int ii = 0; ii < input.size(); ii++){

			}


			string phrase = input[0];
			input.erase(input.begin());
			if(!match_phrase(sequence, position, phrase)){
				input.push_back(phrase);
			} else{
				temp_output = construct_sequence(sequence, position);
				printf("%s  -  %s\n",phrase.c_str(), temp_output.c_str());
			}

		}
	}


	return construct_sequence(sequence, position);
}

int match_phrase(string intial, string input, int &pos){
	string buffer(input.length()-1,  blank_char);

	string cur = buffer + intial;

	vector<int> matches;
	vector<int> match_intensity;

	int max_offset = cur.length();
	cur = cur + buffer;

	for(int ii = 0; ii < max_offset; ii++){
		bool match_found = false, no_mismatch = true;
		int match = 0;

		for(int jj = 0; jj < input.length(); jj++){
			char c_c = cur[ii+jj], c_i = input[jj];

			if(c_c != blank_char){
				if(c_c != c_i){
					no_mismatch = false;
					break;
				} else{
					match_found = true;
					match++;
				}
			}
		}
		if(no_mismatch && match_found){
			matches.push_back(ii);
			match_intensity.push_back(match);
		}
	}

	int match_to_use = 0;

	if(matches.size() == 0)
		return -1;
	else if(matches.size() > 1){
		int m_int = match_intensity[0];
		for(int ii = 0; ii < matches.size(); ii++){
			if(m_int < match_intensity[ii]){
				match_to_use = ii;
				m_int = match_intensity[ii];
			}
		}

	}


	pos = matches[match_to_use];
	/*if(p < input.length()){
		pos.push_back(0);
		p = input.length() - p-1;
		for(int ii = 0; ii < pos.size()-1; ii++)
			pos[ii] += p;
	} else{
		pos.push_back(matches[match_to_use]-input.length() + 1);
	}*/

	return match_intensity[match_to_use];
}

string construct_sequence(vector<string> &seq, vector<int> &pos){
	string s = "";
	int pp = 0;
	vector<string> build;
	int max_length = 0;

	for(int ii = 0; ii < pos.size(); ii++){
		string buffer(pos[ii], blank_char);
		build.push_back(buffer + seq[ii]);
		if(build.back().length() > max_length)
			max_length = build.back().length();
	}

	for(int ii = 0; ii < build.size(); ii++){
		if(build[ii].length() < max_length){
			string buffer(max_length-build[ii].length(), blank_char);
			build[ii] = build[ii] + buffer;
		}
	}

	for(int ii = 0; ii < max_length; ii++){
		char c = blank_char;
		for(int jj = 0; jj < build.size(); jj++){
			if(build[jj][ii] != blank_char){
				if(c != blank_char && c != build[jj][ii]){
					printf("mismatch");
				} else{
					c = build[jj][ii];
				}
			}
		}
		s += c;
	}

	return s;
}

void read_in_sequence(string input_file, vector<string> &strs, int read_version){
	ifstream infile;
	infile.open(input_file.c_str());
	string line;

	while(getline(infile, line)){
		if(read_version == 0){
			strs.push_back(line);
		} else if(read_version == 1){
			int opening_quote = -1, closing_quote = -1;
			bool looking_for_opening = true;
			for(int ii = 0; ii < line.length(); ii++){
				if(line[ii] == '[' && looking_for_opening){
					opening_quote = ii;
					looking_for_opening = false;
				} else if(line[ii] == ']' && !looking_for_opening){
					closing_quote = ii;
					looking_for_opening = true;
					strs.push_back(line.substr(opening_quote+1, closing_quote-opening_quote-1));
				}
			}
		}
	}

	infile.close(); 

}



void print_list(vector<string> &list){
	for(int ii = 0; ii < list.size(); ii++){
		printf("%s\n", list[ii].c_str());
	}
}

void print_list(vector<int> &list){
	for(int ii = 0; ii < list.size(); ii++){
		printf("%d\n", list[ii]);
	}
}

