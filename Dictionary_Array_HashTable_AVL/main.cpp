#include"utilities.h"
#include"array.h"
#include"hashTable.h"
int main() 
{
	string inc_1[3] = { "Array", "Hash Table", "AVL Tree" };
	string inc_2[6] = { "Load", "Save", "Look up","Insert","Edit","Remove" }; 
	int core, cmd; 
	cout << "Choose dictionary's core (0-1) :\n0. Array\n1. Hash Table\n>>"; 
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
			if (cmd == 6)
				break; 
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
		delete[] dictionary; 
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
			if (cmd == 6)
				break;
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
		for (int i = 0; i < sizeHashTable; i++) {
			freedomForLL(hashTable[i].head);
		}
		delete[] hashTable; 
	}
	return 0;
}