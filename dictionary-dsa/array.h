#ifndef _ARRAY_H_
#define _ARRAY_H_
#include"utilities.h"
void swap(word& a, word& b);
void quickSort(word dic[], int left, int right);
int binarySearch(word dictionary[], int left, int right, string key); 
word filter(string raw);
void readFileArray(word* &dictionary, int& size, word dicT[]);
void writeFileArray(word* dictionary, int size); 
void findingWordArray(word* dictionary, int size);
void insertingWordArray(word* dictionary, int size); 
void editingWordArray(word* dictionary, int size); 
void deletingWordArray(word* dictionary, int size);
#endif // !_ARRAY_H_

