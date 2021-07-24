#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#include<iostream>
#include<fstream>
#include<string>
#include<chrono>
#include<vector>
#include <cstdlib>
#include <ctime>
#define NUM_LINE 72320
#define SOURCE_DATASET "Oxford-English-Dictionary.txt"
#define RESULT_SET "EnglishDictionaryfromOxford.txt"
#define INP_DESTINATION "input.txt"
#define OUT_DESTINATION "output.txt"
#define UTF8_ENCRYPTED_MASK "3NcRyPt3d"
#define OUTLIER_HASHING_STRING "CoMputErsCiEnceiSmYlIf3333"
using namespace std; 
using chrono::steady_clock; 
using chrono::duration; 
struct hashElement {
	wstring keyword;
	wstring meaning;
};
struct Node {
	hashElement element;
	Node* next;
};

struct word {
	string encrypted; 
	string cmp; 
	string in; 
	string mean; 
};

struct headNode {
	Node* head;
};

struct nodeBST {
	wstring keyword; 
	wstring meaning; 
	nodeBST* left;
	nodeBST* right;
};
struct BinarySearchTree {
	nodeBST* root;
};

struct nodeAVL {
	wstring keyword;
	wstring meaning; 
	int weight;
	nodeAVL* lChild;
	nodeAVL* rChild;
};
struct AVLTree {
	nodeAVL* root;
};
int max(int& a, int& b); 

void swapHE(hashElement& a, hashElement& b); 

string formalize(string w); 
string encrypt(string root);

wstring wformalize(wstring w);
hashElement wfilter(wstring raw);

int locatePrime(int size);
#endif // !_UTILITIES_H_

