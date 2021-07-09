#include"hashTable.h"

int hashingFunction(wstring keyword, int modu) {
	int accumulator = 777; 
	for (int i = 0; i < keyword.length(); i++)
		accumulator += int(keyword[i])*10; 
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
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
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
		if (t3.length() > 2) {
			fi3 = wfilter(t3);
			if (fi2.keyword == L"Usage") {
				wcout << fi1.keyword << L" " << fi2.keyword << L" " << fi3.keyword << endl;
				wcout << (fi3.keyword >= fi2.keyword) << " " << (fi1.keyword <= fi2.keyword) << endl;
			}
			if (fi2.keyword == L"Usage" && !((fi3.keyword >= fi2.keyword) && (fi1.keyword <= fi2.keyword))) {
				fi1.meaning += L"\n Usage : " + fi2.meaning;
				fi2 = fi3; 
				continue; 
			}
			else if (fi3.keyword == L"") {
				fi2.meaning += L"\n " + fi3.meaning; 
				continue; 
			}
			else if (fi2.keyword == fi3.keyword && fi2.meaning == fi3.meaning) {
				continue; 
			}
			else {
				pushNode(hashTable[hashingFunction(fi1.keyword, sizeHashTable)].head, fi1);
				fi1 = fi2;
				fi2 = fi3;
			}
		}
	}
	pushNode(hashTable[hashingFunction(fi2.keyword, sizeHashTable)].head, fi2);
	pushNode(hashTable[hashingFunction(fi3.keyword, sizeHashTable)].head, fi3);
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
}
void swapHE(hashElement& a, hashElement& b) {
	hashElement c = a; 
	a = b; 
	b = c;
}
int partition(hashElement* array, int left, int right) {
	int j = left; 
	for (int i = left ; i < right ; i++)
		if (array[i].keyword < array[right].keyword) 
			swap(array[i], array[++j]); 
	swap(array[right], array[++j]); 
	return j; 
}

void quickSortHE(hashElement* array, int left, int right) {
	if (left >= right) return;
	int mid = partition(array, left, right); 
	quickSortHE(array, left, mid - 1); 
	quickSortHE(array, mid + 1, right); 
}
void writeFileHashTable(headNode* hashTable, int size) {
	wfstream fo(RESULT_SET, ios::out);
	// quickSort(dictionary, 0, size);
	hashElement *temp = new hashElement[NUM_LINE / 2]; 
	int d = 0; 
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	for (int i = 0; i < size; i++) {
		// traverse(hashTable[i].head, fo);
		Node* head = hashTable[i].head;
		while (head) {
			temp[d++] = head->element; 
			head = head->next; 
		}
	}
	quickSortHE(temp, 0, size); 
	for (int i = 0; i < size; i++)
		fo << temp[i].keyword << " : " << temp[i].meaning << endl; 
	cout << "Save to " << RESULT_SET << " sucessfully !\n";
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fo.close();
	delete[] temp; 
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
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	Node* p = searchWordHashTable(hashTable, size, wformalize(key));
	if (!p) {
		fo << "Not Found\n";
		cout << "Not Found\n";
	}
	else {
		fo << p->element.keyword << L" : " << p->element.meaning<< endl;
		cout << "Found\n";

	}
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
	fo.close();
	system(OUT_DESTINATION);
}
void insertingWordHashTable(headNode* hashTable, int size) {
	wstring temp;
	wcin.ignore();
	wfstream fi(INP_DESTINATION, ios::in);
	cout << "Enter the word that you want to insert in the " << INP_DESTINATION << "\nFormat: Keyword 2 spaces Meaning\n";
	system(INP_DESTINATION);
	getline(fi, temp);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	temp = wformalize(temp);
	hashElement fil = wfilter(temp);
	Node* p = newNode(fil); 
	pushNode(hashTable[hashingFunction(fil.keyword, size)].head, fil); 
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
}
void editingWordHashTable(headNode* hashTable, int size) {
	wstring temp;
	wcin.ignore();
	wfstream fi(INP_DESTINATION, ios::in);
	cout << "Enter the keyword and the new meaning that you want to edit in the " << INP_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, temp);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	hashElement fil = wfilter(temp);
	Node* p = searchWordHashTable(hashTable, size, wformalize(fil.keyword));
	if (!p) {
		cout << "Not Found\n";
	}
	else {
		p->element = fil;
		cout << "Edited!\n";
	}
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
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
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	temp = wformalize(temp); 
	if (deleteNode(hashTable[hashingFunction(temp, size)].head, temp))
		cout << "Deleted !\n";
	else
		cout << "The keyword is not exist! \n"; 
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
}