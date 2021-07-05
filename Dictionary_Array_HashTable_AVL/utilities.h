#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#include<iostream>
#include<fstream>
#include<string>
#define NUM_LINE 72320
#define SOURCE_DATASET "Oxford-English-Dictionary.txt"
#define RESULT_SET "EnglishDictionaryfromOxford.txt"
#define INP_DESTINATION "input.txt"
#define OUT_DESTINATION "output.txt"
#define UTF8_ENCRYPTED_MASK "3NcRyPt3d"
#define OUTLIER_HASHING_STRING "CoMputErsCiEnceiSmYlIf3333"
using namespace std;
struct word {
	string encrypted; 
	string cmp; 
	string in; 
	string mean; 
};
string formalize(string w); 
string encrypt(string root);
#endif // !_UTILITIES_H_

