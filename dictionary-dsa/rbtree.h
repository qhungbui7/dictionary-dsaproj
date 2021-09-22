#ifndef _RBTREE_H_
#define _RBTREE_H_
#include"utilities.h"
#define RED true 
#define BLACK false 



nodeRB* newRBNode(wstring keyword, wstring meaning); 
bool getColor(nodeRB* p); 
void assignColor(nodeRB*& p, bool color); 
int checkProb(nodeRB* p, nodeRB*& par, nodeRB*& sib);
nodeRB* leftRotation(nodeRB* sib, nodeRB* par, RedBlackTree& rb);
nodeRB* rightRotation(nodeRB* sib, nodeRB* par, RedBlackTree& rb);
void swapColor(nodeRB* a, nodeRB* b);
nodeRB* judgment(nodeRB* grandpar, RedBlackTree rb);
nodeRB* pushNode(nodeRB* p, nodeRB* t, RedBlackTree rb);
void initialize(RedBlackTree& RBTree); 
void destroyRBTree(nodeRB*& p);
nodeRB* searchRB(nodeRB* p, wstring key);
void update(nodeRB* grandpar, bool isGrandparLeft);
void fixDoubleBlack(nodeRB*& grandpar, bool isLeft, RedBlackTree& rb);
void deleteNodeRB(nodeRB*& p, wstring x, RedBlackTree& rb);
bool isTreeEmpty(RedBlackTree rb);
void traverseAVL(nodeAVL* p, wfstream& fo);
void traverseRB(nodeRB* p, wfstream& fo);
void readFileRB(RedBlackTree& rb);
void writeFileRB(RedBlackTree rb);
void findingWordRB(RedBlackTree rb);
void insertingWordRB(RedBlackTree rb);
void editingWordRB(RedBlackTree rb);
void deletingWordRB(RedBlackTree rb);



#endif // !_RBTREE_H_
