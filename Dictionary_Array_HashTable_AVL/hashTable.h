#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_
#include"utilities.h"


int hashingFunction(wstring keyword, int modu);


Node* newNode(hashElement element);
void pushNode(Node*& head, hashElement element);
bool deleteNode(Node* head, wstring keyword); 
void freedomForLL(Node* p); 

void readFileHashTable(headNode* hashTable, int modu);
void writeFileHashTable(headNode* hashTable, int size);
Node* searchWordHashTable(headNode* hashTable, int size, wstring key);
void findingWordHashTable(headNode* hashTable, int size);
void insertingWordHashTable(headNode* hashTable, int size);
void editingWordHashTable(headNode* hashTable, int size);
void deletingWordHashTable(headNode* hashTable, int size);


#endif // !_HASHTABLE_H_
