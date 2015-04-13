#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string sequence(string input_file, int read_version);
void read_in_sequence(string input_file, vector<string> &strs, int read_version);
int match_phrase(string intial, string input, int &pos);
string combine_strings(string phrase, string input, int position);

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

/*Solves in O(k^2*n) time, where k is the number of input strings, and n is the length */
string sequence(string input_file, int read_version){
	vector<string> input, unable_to_match;
	int input_number = -1;
	read_in_sequence(input_file, input, read_version);

	while(input.size() > 1){
		string phrase = input[0];
		input.erase(input.begin());
		int best_intensity = 0, best_position = 0;
		string best_phrase = "";
		for(int ii = 0; ii < input.size(); ii++){
			int cur_position, cur_intensity;
			cur_intensity = match_phrase(phrase, input[ii], cur_position);
			if(cur_intensity > best_intensity){
				best_intensity = cur_intensity;
				best_position = cur_position;
				best_phrase = input[ii];
				input_number = ii;
			}
		}
		if(best_intensity > 0){
			phrase = combine_strings(phrase, best_phrase, best_position);
			input.push_back(phrase);
			vector<string>::iterator iter = input.begin();
			iter += input_number;
			input.erase(iter);
		} else{
			unable_to_match.push_back(phrase);
		}
	}
	if(unable_to_match.size() > 0){
		printf("Unable to match all entries.\n");
		string combine = "";
		for(int ii = 0; ii < unable_to_match.size(); ii++){
			combine += unable_to_match[ii];
		}
		return combine;
	}
	return input[0];
}

/* Combines in O(n) time */
string combine_strings(string phrase, string input, int position){
	string buffer(input.length()-1, blank_char);
	string buffered_phrase = (buffer + phrase) + buffer, combined = "";
	for(int ii = 0; ii < buffered_phrase.length(); ii++){
		if(ii >= position && ii < position + input.length()){
			combined += input[ii - position];
		}
		else{
			if(buffered_phrase[ii] != blank_char){
				combined += buffered_phrase[ii];
			}
		}
	}

	return combined;
}

/* Matches in O(k*n) time where k is the number of input strings, and n is the length */
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

	return match_intensity[match_to_use];
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


