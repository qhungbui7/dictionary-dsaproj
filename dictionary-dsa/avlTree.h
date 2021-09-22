#ifndef _AVLTREE_H_
#define _AVLTREE_H_
#include"utilities.h"

nodeAVL* newAVLNode(wstring keyword, wstring meaning);
int getWeight(nodeAVL* p); 
nodeAVL* rightRotate(nodeAVL* p); 
nodeAVL* leftRotate(nodeAVL* p); 
nodeAVL* checkAndRotate(nodeAVL* p); 
nodeAVL* pushAVLNode(nodeAVL*& pos, wstring keyword, wstring meaning);
void traverseAVL(nodeAVL* p, wfstream& fo);
void destroyAVLTree(nodeAVL*& p);
void readFileAVL(AVLTree& avl);
void writeFileAVL(AVLTree avl);
nodeAVL* searchWordAVL(nodeAVL* p, wstring key);
void findingWordAVL(AVLTree avl); 
bool isEmptyAVL(AVLTree avl); 
void insertingWordAVL(AVLTree avl); 
void editingWordAVL(AVLTree avl); 
nodeAVL* deleteNodeAVL(nodeAVL* p, wstring keyword); 
void deletingWordAVL(AVLTree avl); 


#endif // !_AVLTREE_H_
