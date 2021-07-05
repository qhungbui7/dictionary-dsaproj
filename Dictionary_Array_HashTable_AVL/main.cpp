#include"utilities.h"
#include"array.h"
int main() 
{
	string inc_1[3] = { "Array", "Hash Table", "AVL Tree" };
	string inc_2[6] = { "Load", "Save", "Look up","Insert","Edit","Remove" }; 
	int core, cmd; 
	cout << "Choose dictionary's core (0-2) :\n0. Array\n1. Hash Table\n2. AVL Tree\n>>"; 
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
	
	return 0;
}