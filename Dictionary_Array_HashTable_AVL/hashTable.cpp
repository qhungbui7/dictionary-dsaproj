#include"hashTable.h"

int hashingFunction(wstring keyword, int modu) {
	int accumulator = 777; 
	for (int i = 0; i < keyword.length(); i++)
		accumulator += int(keyword[i]); 
	return accumulator % modu; 
}

Node* newNode(hashElement element) {
	Node* p = new Node;
	p->element = element;
	p->next = nullptr;
	return p;
}
void pushNode(Node* &head, hashElement element){
	Node* p = newNode(element);
	//wcout << element.keyword << L" " << element.meaning << endl;
	if (!head)
		head = p; 
	else {
		Node *t = head;
		while (t->next) {
			if (t->element.keyword == element.keyword && t->element.meaning == element.meaning) {
				//cout << "OUT\n";
				return;

			}
			t = t->next; 
		}
		t->next = p; 
	}
}

void freedomForLL(Node *p) {
	if (p)
		freedomForLL(p->next); 
	delete p; 
}
void traverse(Node* head, wfstream &fo) {
	while (head) {
		fo << head->element.keyword << " : " << head->element.meaning << endl; 
		head = head->next; 
	}
}
void readFileHashTable(headNode* hashTable, int sizeHashTable) {
	wfstream fi(SOURCE_DATASET, ios::in); 
	wstring t1, t2, t3;
	hashElement fi1, fi2, fi3;
	for (int i = 0; i < sizeHashTable; i++)
		hashTable[i].head = nullptr; 
	while (getline(fi, t1))
		if (t1.length() > 2) {
			fi1 = wfilter(t1);
			break; 
		}
	while (getline(fi, t2))
		if (t2.length() > 2){ 
			fi2 = wfilter(t2);
			break;
		}
 
	while (getline(fi, t3)) {
		//wcout << t3 << endl; 
		if (t3.length() > 2) {
			//cout << "C1\n"; 
			fi3 = wfilter(t3);
			//wcout << fi3.keyword << L"\n" << fi3.meaning << endl; 
			if (fi2.keyword == L"Usage" && !(fi3.keyword <= L"Usage" && fi1.keyword >= L"Usage")) {
				fi1.meaning += L"\n Usage : " + fi2.meaning;
				fi2 = fi3; 
				continue; 
			}
			else if (fi3.keyword == L"") {
				fi2.meaning += L"\n " + fi3.meaning; 
				continue; 
			}
			//cout << "C1.5\n"; 
			pushNode(hashTable[hashingFunction(fi1.keyword, sizeHashTable)].head, fi1); 
			//cout << "C2\n";
			fi1 = fi2; 
			fi2 = fi3; 
		}
	}
	pushNode(hashTable[hashingFunction(fi2.keyword, sizeHashTable)].head, fi2);
	pushNode(hashTable[hashingFunction(fi3.keyword, sizeHashTable)].head, fi3);
}
void writeFileHashTable(headNode* hashTable, int size) {
	wfstream fo(RESULT_SET, ios::out);
	// quickSort(dictionary, 0, size);

	for (int i = 0; i < size; i++) {
		traverse(hashTable[i].head, fo);
	}
	cout << "Save to " << RESULT_SET << " sucessfully !\n";
	fo.close();
	system(RESULT_SET);
}
Node* searchWordHashTable(headNode* hashTable, int size, wstring key) {
	headNode element = hashTable[hashingFunction(key, size)];
	Node* p = element.head; 
	while (p) {
		if (p->element.keyword == key)
			break; 
		p = p->next; 
	}
	return p; 
}
void findingWordHashTable(headNode* hashTable, int size) {
	wstring key;
	wcin.ignore();

	wfstream fi(INP_DESTINATION, ios::in);
	wfstream fo(OUT_DESTINATION, ios::out);
	cout << "Enter the word that you want to find in the " << INP_DESTINATION << ", output in the " << OUT_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, key);
	Node* p = searchWordHashTable(hashTable, size, wformalize(key));
	if (!p) {
		fo << "Not Found\n";
		cout << "Not Found\n";
	}
	else {
		fo << p->element.keyword << L" : " << p->element.meaning<< endl;
		cout << "Found\n";

	}
	fi.close();
	fo.close();
	system(OUT_DESTINATION);
}
void insertingWordHashTable(headNode* hashTable, int size) {
	wstring temp;
	wcin.ignore();
	wfstream fi(INP_DESTINATION, ios::in);
	cout << "Enter the word that you want to insert in the " << INP_DESTINATION << "\nFormat :Keyword 2 spaces Meaning\n";
	system(INP_DESTINATION);
	getline(fi, temp);
	temp = wformalize(temp);
	hashElement fil = wfilter(temp);
	Node* p = newNode(fil); 
	pushNode(hashTable[hashingFunction(fil.keyword, size)].head, fil); 
	fi.close();
}
void editingWordHashTable(headNode* hashTable, int size) {
	wstring temp;
	wcin.ignore();
	wfstream fi(INP_DESTINATION, ios::in);
	cout << "Enter the keyword and the new meaning that you want to edit in the " << INP_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, temp);
	hashElement fil = wfilter(temp);
	Node* p = searchWordHashTable(hashTable, size, wformalize(fil.keyword));
	if (!p) {
		cout << "Not Found\n";
	}
	else {
		p->element = fil;
		cout << "Edited!\n";
	}
	fi.close();
}
bool deleteNode(Node* head, wstring keyword) {
	if (!head) return false;
	Node* p = head;
	Node* pre = head;
	bool check = false;
	if (head->element.keyword == keyword) {
		head = head->next;
		delete p;
	}
	else {
		p = p->next;
		while (p) {
			if (p->element.keyword == keyword) {
				pre->next = p->next;
				delete p;
				check = true; 
				break; 
			}
			else {
				pre = p; 
				p = p->next;
			}
		}
	}
	return check;
}
void deletingWordHashTable(headNode* hashTable, int size) {
	wstring temp;
	wcin.ignore();
	wfstream fi(INP_DESTINATION, ios::in);
	cout << "Enter the word that you want to delete in the " << INP_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, temp);
	temp = wformalize(temp); 
	if (deleteNode(hashTable[hashingFunction(temp, size)].head, temp))
		cout << "Deleted !\n";
	else
		cout << "The keyword is not exist! \n"; 
	fi.close();
}