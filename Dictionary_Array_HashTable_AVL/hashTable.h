#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_
#include"utilities.h"

struct hashElement {
	wstring keyword; 
	wstring meaning; 
};
struct headNode {
	int key; 
	Node* head; 
};
struct Node {
	hashElement element; 
	Node* next; 
};

int locatePrime(int size); 
int hashingFunction(wstring keyword, int modu);

wstring wformalize(wstring w); 
hashElement wfilter(wstring raw);

Node* newNode(hashElement element);
void pushNode(Node*& head, hashElement element);
void deleteNode(Node* head, wstring keyword); 

void readFileHashTable(headNode * hashTable, int modu);


#endif // !_HASHTABLE_H_
