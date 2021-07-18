#ifndef _BINARYSEARCHTREE_H_
#define _BINARYSEARCHTREE_H_
#include"utilities.h"

void initialize(BinarySearchTree& bst); 
nodeBST* newNodeBST(wstring keyword, wstring meaning);
nodeBST* pushNodeBST(nodeBST* p, wstring keyword, wstring meaning);
void readFileBST(BinarySearchTree &bst);
void traverseBST(nodeBST* p, wfstream& fo);
void writeFileBST(BinarySearchTree bst); 
nodeBST* searchWordBST(nodeBST* p, wstring key);
void findingWordBST(BinarySearchTree bst); 
void insertingWordBST(BinarySearchTree bst); 
void editingWordBST(BinarySearchTree bst);
nodeBST* deleteNodeBST(nodeBST* p, wstring keyword);
void deletingWordBST(BinarySearchTree bst);



#endif // !_BINARYSEARCHTREE_H_
