#include"hashTable.h"
int locatePrime(int size) {
	int p = size; 
	while (true) {
		bool chk = true; 
		for (int i = 2 ; i < int(sqrt(size)) ; i++)
			if (p % i == 0) {
				chk = false; 
				break; 
			}
		if (chk) 
			return p; 
		p--; 
	}
}
int hashingFunction(wstring keyword, int modu) {
	int accumulator = 777; 
	for (int i = 0; i < keyword.length(); i++)
		accumulator += int(keyword[i]); 
	return accumulator % modu; 
}

wstring wformalize(wstring w) {
	if (w[0] == '-')
		w = w.substr(1, w.length());
	w[0] = toupper(w[0]);
	for (int i = 1; i < w.length(); i++)
		w[i] = tolower(w[i]);
	return w;
}
hashElement wfilter(wstring raw) {
	hashElement t;
	for (int i = 0; i < raw.length() - 1; i++)
		if (raw[i] == ' ' && raw[i + 1] == ' ') {
			t.keyword = raw.substr(0, i);
			while (t.keyword[0] == ' ') {
				t.keyword.erase(0, 1);
			}
			t.keyword = wformalize(t.keyword); 
			t.meaning = raw.substr(i + 2, raw.length() - 1 - (i + 2) + 1);
			break;
		}

	return t;
}

Node* newNode(hashElement element) {
	Node* p = new Node;
	p->element = element;
	p->next = nullptr;
	return p;
}
void pushNode(Node* &head, hashElement element){
	Node* p = newNode(element);
	if (!head)
		head = p; 
	else {
		Node *t = head;
		while (t->next)
			if (t->element.keyword == element.keyword && t->element.meaning == element.meaning) {
				return; 
			}
		t->next = p; 
	}
}
void deleteNode(Node* head, wstring keyword) {
	Node* p = head;
	if (head->element.keyword == keyword) {
		head = p->next;
		delete p;
	}
	else {
		while (p->next) {
			if (p->next->element.keyword == keyword) {
				Node* t = p->next; 
				p->next = p->next->next; 
				delete t; 
			}
		}
	}
}
//void freedomForLL() {

//}
void readFileHashTable(headNode* hashTable, int modu) {
	wfstream fi(SOURCE_DATASET, ios::in); 
	wstring t1, t2, t3;
	hashElement fi1, fi2, fi3; 
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
			if (fi2.keyword == L"Usage" && !(fi3.keyword <= L"Usage" && fi1.keyword >= L"Usage")) {
				fi1.meaning += L"\n Usage : " + fi2.meaning;
				fi2 = fi3; 
				continue; 
			}
			else if (fi3.keyword == L"") {
				fi2.meaning += L"\n " + fi3.meaning; 
				continue; 
			}
			pushNode(hashTable[hashingFunction(fi1.keyword, modu)].head, fi1); 
			fi1 = fi2; 
			fi2 = fi3; 
		}
	}
	pushNode(hashTable[hashingFunction(fi2.keyword, modu)].head, fi2);
	pushNode(hashTable[hashingFunction(fi3.keyword, modu)].head, fi3);
}