#include"binarySearchTree.h"
void initialize(BinarySearchTree& bst) {
	bst.root = nullptr; 
}
nodeBST* newNodeBST(wstring keyword, wstring meaning){
	nodeBST *p = new nodeBST;
	p->keyword = keyword; 
	p->meaning = meaning; 
	p->left = nullptr; 
	p->right = nullptr; 
	return p; 
}
nodeBST *pushNodeBST(nodeBST *p, wstring keyword, wstring meaning) {
	if (!p) {
		p = newNodeBST(keyword, meaning); 
	}
	else {
		if (p->keyword < keyword)
			p->right = pushNodeBST(p->right, keyword, meaning); 
		else if (p->keyword > keyword)
			p->left = pushNodeBST(p->left, keyword, meaning);
	}
	return p; 
}

void readFileBST(BinarySearchTree &bst) {
	wfstream fi(SOURCE_DATASET, ios::in);
	vector< hashElement > temp; 
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	wstring t1, t2, t3;
	hashElement fi1, fi2, fi3;
	srand(time(NULL)); 
	while (getline(fi, t1))
		if (t1.length() > 2) {
			fi1 = wfilter(t1);
			break;
		}
	while (getline(fi, t2))
		if (t2.length() > 2) {
			fi2 = wfilter(t2);
			break;
		}
	while (getline(fi, t3)) {
		if (t3.length() > 2) {
			fi3 = wfilter(t3);
			//if (fi2.keyword == L"Usage" && fi2.meaning[0] == L'n')
				//wcout << fi2.keyword << " " << fi2.meaning << endl; 
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
				//if (fi1.keyword == L"Usage")
				//	wcout << fi1.meaning << endl;
				//if (fi1.keyword == L"Usage" && fi1.meaning[0] == L'n')
				//wcout << fi1.keyword << " " << fi1.meaning << endl; 
				temp.push_back(fi1); 
				fi1 = fi2;
				fi2 = fi3;
			}
		}
	}
	temp.push_back(fi2);
	temp.push_back(fi3);
	for (int i = temp.size() - 1; i >= 0; i--) {
		int pos = (rand() % (i + 1)); 
		bst.root = pushNodeBST(bst.root, temp[pos].keyword, temp[pos].meaning); 
		swapHE(temp[pos], temp[i]); 
	}


	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
}

void traverseBST(nodeBST *p, wfstream &fo) {
	if (p) {
		traverseBST(p->left, fo); 
		fo << p->keyword << " : " << p->meaning << endl; 
		traverseBST(p->right, fo); 
	}

}

void writeFileBST(BinarySearchTree bst) {
	wfstream fo(RESULT_SET, ios::out);
	// quickSort(dictionary, 0, size);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();

	traverseBST(bst.root, fo); 

	cout << "Save to " << RESULT_SET << " sucessfully !\n";
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fo.close();
	system(RESULT_SET);

}


nodeBST* searchWordBST(nodeBST *p, wstring key) {
	if (!p)
		return nullptr; 
	else {
		if (p->keyword == key)
			return p;
		else if (p->keyword < key)
			return searchWordBST(p->right, key);
		else
			return searchWordBST(p->left, key); 
	}
}
void findingWordBST(BinarySearchTree bst) {
	wstring key;
	wcin.ignore();

	wfstream fi(INP_DESTINATION, ios::in);
	wfstream fo(OUT_DESTINATION, ios::out);
	cout << "Enter the word that you want to find in the " << INP_DESTINATION << ", output in the " << OUT_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, key);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	nodeBST* p = searchWordBST(bst.root, wformalize(key));
	if (!p) {
		fo << "Not Found\n";
		cout << "Not Found\n";
	}
	else {
		fo << p->keyword << L" : " << p->meaning << endl;
		cout << "Found\n";

	}
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
	fo.close();
	system(OUT_DESTINATION);
}
void insertingWordBST(BinarySearchTree bst) {
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
	nodeBST* p = newNodeBST(fil.keyword, fil.meaning);

	if (searchWordBST(bst.root, fil.keyword))
		cout << "Terminated, word is already exist!\n";
	else {
		//wcout << fil.keyword << endl; 
		//wcout << fil.meaning << endl; 
		bst.root = pushNodeBST(bst.root, fil.keyword, fil.meaning);
		cout << "Insert sucessfully!\n"; 
	}
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
}
void editingWordBST(BinarySearchTree bst) {
	wstring temp;
	wcin.ignore();
	wfstream fi(INP_DESTINATION, ios::in);
	cout << "Enter the keyword and the new meaning that you want to edit in the " << INP_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, temp);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	hashElement fil = wfilter(temp);
	nodeBST* p = searchWordBST(bst.root, wformalize(fil.keyword));
	if (!p) {
		cout << "Not Found\n";
	}
	else {
		//p->keyword = fil.keyword;
		p->meaning = fil.meaning; 
		cout << "Edited!\n";
	}
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
}
nodeBST* deleteNodeBST(nodeBST* p, wstring keyword) {
	if (!p)
		return nullptr; 
	else {
		if (p->keyword < keyword)
			p->right = deleteNodeBST(p->right, keyword); 
		else if (p->keyword > keyword)
			p->left = deleteNodeBST(p->left, keyword);
		else {
			if (!p->left && !p->right) {
				delete p;
				p = nullptr;
				return p;
			}
			else if (p->left && !p->right) {
				nodeBST* t = p->left;
				delete p;
				p = nullptr; 
				return t; 
			}
			else if (!p->left && p->right) {
				nodeBST* t = p->right; 
				delete p;
				p = nullptr;
				return t;
			}
			else {
				nodeBST* t = p->right; 
				while (t->left)
					t = t->left; 
				p->keyword = t->keyword; 
				p->right = deleteNodeBST(p->right, p->keyword); 
			}
		}
	}
	return p;
}
void deletingWordBST(BinarySearchTree bst) {
	wstring temp;
	wcin.ignore();
	wfstream fi(INP_DESTINATION, ios::in);
	cout << "Enter the word that you want to delete in the " << INP_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, temp);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	temp = wformalize(temp);
		
	if (!searchWordBST(bst.root,temp))
		cout << "The keyword is not exist! \n";
	else {
		bst.root = deleteNodeBST(bst.root, temp); 
		cout << "Deleted !\n";
	}
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
}