#include"utilities.h"
#include"array.h"
#include"hashTable.h"
#include"binarySearchTree.h"
#include"rbtree.h"
#include"avlTree.h"
int main() 
{
	string inc_1[5] = { "Array", "Hash Table", "Binary Search Tree", "AVL Tree", "Red Black Tree"};
	string inc_2[6] = { "Load", "Save", "Look up","Insert","Edit","Remove" }; 
	int core, cmd; 
	cout << "Choose dictionary's core (0-3) :\n0. Array\n1. Hash Table\n2. Binary Search Tree\n3. AVL Tree\n4.Red Black Tree\n>>"; 
	wcin >> core; 
	if (core == 0) {
		word* dictionary = new word[NUM_LINE];
		word* dicT = new word[NUM_LINE]; 
		int size = 0;
		while (true) {
			cout << "Choose function (0 - 6) :\n";
			for (int inc = 0; inc < 6; inc++) {
				cout << inc << ". " << inc_2[inc] << endl;
			}
			cout << "6. Exit\n>>";
			cin >> cmd;
			if (cmd == 6) {
				delete[] dictionary;
				break;
			}
			else if (cmd == 0) 
				readFileArray(dictionary, size, dicT); 
			else if (cmd == 1) 
				writeFileArray(dictionary, size); 
			else if (cmd == 2) 
				findingWordArray(dictionary, size); 
			else if (cmd == 3) 
				insertingWordArray(dictionary, size); 
			else if (cmd == 4) 
				editingWordArray(dictionary, size); 
			else if (cmd == 5) 
				deletingWordArray(dictionary, size); 
		}

	}
	else if (core == 1) {
		int sizeHashTable = locatePrime(NUM_LINE / 7); 
		headNode* hashTable = new headNode[sizeHashTable];
		while (true) {
			cout << "Choose function (0 - 6) :\n";
			for (int inc = 0; inc < 6; inc++) {
				cout << inc << ". " << inc_2[inc] << endl;
			}
			cout << "6. Exit\n>>";
			cin >> cmd;
			if (cmd == 6) {
				for (int i = 0; i < sizeHashTable; i++) {
					freedomForLL(hashTable[i].head);
				}
				delete[] hashTable;
				break;
			}
			else if (cmd == 0)
				readFileHashTable(hashTable, sizeHashTable);
			else if (cmd == 1)
				writeFileHashTable(hashTable, sizeHashTable);
			else if (cmd == 2)
				findingWordHashTable(hashTable, sizeHashTable);
			else if (cmd == 3)
				insertingWordHashTable(hashTable, sizeHashTable);
			else if (cmd == 4)
				editingWordHashTable(hashTable, sizeHashTable);
			else if (cmd == 5)
				deletingWordHashTable(hashTable, sizeHashTable);
		}

	}
	else if (core == 2) {
		BinarySearchTree bst; 
		initialize(bst); 
		while (true) {
			cout << "Choose function (0 - 6) :\n";
			for (int inc = 0; inc < 6; inc++) {
				cout << inc << ". " << inc_2[inc] << endl;
			}
			cout << "6. Exit\n>>";
			cin >> cmd;
			if (cmd == 6) {
				destroyTree(bst.root);
				break;
			}
			else if (cmd == 0)
				readFileBST(bst); 
			else if (cmd == 1)
				writeFileBST(bst);
			else if (cmd == 2)
				findingWordBST(bst);
			else if (cmd == 3)
				insertingWordBST(bst);
			else if (cmd == 4)
				editingWordBST(bst);
			else if (cmd == 5)
				deletingWordBST(bst);
		}
	}
	else if (core == 3) {
		AVLTree avl;
		avl.root = nullptr; 
		while (true) {
			if (isEmptyAVL(avl))
				cout << "Tree is empty now !\n";
			else
				cout << "Tree is not empty now !\n";
			cout << "Choose function (0 - 6) :\n";
			for (int inc = 0; inc < 6; inc++) {
				cout << inc << ". " << inc_2[inc] << endl;
			}
			cout << "6. Exit\n>>";
			cin >> cmd;

			
			if (cmd == 6) {
				destroyAVLTree(avl.root);
				break;
			}
			else if (cmd == 0)
				readFileAVL(avl);
			else if (cmd == 1)
				writeFileAVL(avl);
			else if (cmd == 2)
				findingWordAVL(avl);
			else if (cmd == 3)
				insertingWordAVL(avl);
			else if (cmd == 4)
				editingWordAVL(avl);
			else if (cmd == 5)
				deletingWordAVL(avl); 
		}
	}
	else if (core == 4) {
		RedBlackTree rb;
		initialize(rb); 
		while (true) {
			if (isTreeEmpty(rb))
				cout << "Tree is empty now !\n";
			else
				cout << "Tree is not empty now !\n";
			cout << "Choose function (0 - 6) :\n";
			for (int inc = 0; inc < 6; inc++) {
				cout << inc << ". " << inc_2[inc] << endl;
			}
			cout << "6. Exit\n>>";
			cin >> cmd;


			if (cmd == 6) {
				destroyRBTree(rb.root);
				break;
			}
			else if (cmd == 0)
				readFileRB(rb);
			else if (cmd == 1)
				writeFileRB(rb);
			else if (cmd == 2)
				findingWordRB(rb);
			else if (cmd == 3)
				insertingWordRB(rb);
			else if (cmd == 4)
				editingWordRB(rb);
			else if (cmd == 5)
				deletingWordRB(rb);
		}
	}
	return 0;
}