#ifndef MYBLOOMFILTER_H
#define MYBLOOMFILTER_H

#include "bloomfilter.h"
#include <vector>
#include <stdio.h>

#define VERIFY_FILTER

class MyBloomFilter : BloomFilter{
public:
	MyBloomFilter(int mm) : BloomFilter(mm){
		if(mm > 0){
			filter = new char[mm];
			length = mm;
			for(int ii =0; ii < mm; ii++){
				filter[ii] = char(0);
			}
		}
	}

	MyBloomFilter(string f) : BloomFilter(f){
		filter = new char[f.length()];
		for(int ii = 0; ii < f.length(); ii++)
			filter[ii] = f[ii];
	}

	string output(){
		string o = "";
		for(int ii = 0; ii < length; ii++){
			o += filter[ii];
		}
		return o;
	}

	string outputFilterBits(){
		string o = "";
		for(ii = 0; ii < length; ii++){
			o += convert_to_base_2(filter[ii]);
			o += " ";
		}
	}

	string outputBits(string item){
		string o = "";
		for(ii = 0; ii < item.length(); ii++){
			o += convert_to_base_2(item[ii]);
			o += " ";
		}
	}


	void insert(string item){
		vector<string> hashed = hash(item);
		for(int ii = 0; ii < hashed.size(); ii++){
			for(int jj = 0; jj < length; jj++){
				filter[jj] |= hashed[ii][jj];
			}
		}
		#ifdef VERIFY_FILTER
		verification_strings.push_back(item);
		#endif
	}

	bool exists(string item){
		bool answer = true;
		vector<string> hashed = hash(item);
		cout<<hashed[0]<<endl;
		for(int ii = 0; ii < hashed.size(); ii++){
			for(int jj = 0; jj < length; jj++){
				if(filter[jj] & hashed[ii][jj] != hashed[ii][jj])
					answer =  false;
			}
		}	
		#ifdef VERIFY_FILTER
		verify(item, answer);
		#endif
		return answer;
	}

	#ifdef VERIFY_FILTER
	void print_statistics(){
		int total = (correct + false_positive) + false_negative;
		printf("\n\nBloom Filter Statistics\n");
		printf("Correct = %d, False Positive = %d, False Negative = %d, Total = %d\n", correct, false_positive, false_negative, total);
		printf("False Positive probability = %d, False Negative probability = %d\n", (int)((float)false_positive/(float)total*100.0), (int)((float)false_negative/(float)total*100.0));
		printf("\n\n");
	}

	#endif

private:
	#ifdef VERIFY_FILTER
	vector<string> verification_strings;
	int correct = 0;
	int false_positive = 0;
	int false_negative = 0;
	#endif

	vector<string> hash(string item){
		vector<string> vec;
		vec.push_back(pad_string(item, length, char(0)));
		return vec;
	}

	string pad_string(string item, int length, char c){
		if(item.length() < length){
			for(int ii = 0; ii < length - item.length(); ii++)
				item += c;
		}
		return item;
	}

	string convert_to_base_2(int value){
		string out = '';
		while(value > 0){
			if(value % 2 > 0){
				out = "1" + out;
				value--;
			}
			else
				out = "0" + out;
			value /= 2;
		}
		return out;
	}


	#ifdef VERIFY_FILTER
	void verify(string item, bool answer){
		bool result = false;
		for(int ii = 0; ii < verification_strings.size(); ii++){
			if(verification_strings[ii].compare(item) == 0){
				result = true;
				break;
			}
		}

		if(result == answer){
			correct++;
		} else if(!result && answer)
			false_positive++;
		else if(result && !answer)
			false_negative++;
	}
	#endif



protected:
	char *filter;

};




#endif