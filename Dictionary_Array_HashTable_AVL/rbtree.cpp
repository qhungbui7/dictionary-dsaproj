#include"rbtree.h"

nodeRB* newRBNode(wstring keyword, wstring meaning) {
	nodeRB* p = new nodeRB;
	p->color = RED; // all new node must be red
	p->keyword = keyword;
	p->meaning = meaning;
	p->parent = nullptr;
	p->left = nullptr;
	p->right = nullptr;
	return p;
}
bool getColor(nodeRB* p) {
	if (!p)
		return BLACK;
	else
		return p->color;
}
void assignColor(nodeRB*& p, bool color) {
	if (p)
		p->color = color;
}
int checkProb(nodeRB* p, nodeRB*& par, nodeRB*& sib) { // check null , p is grand parent
	if (getColor(p->left) == RED && getColor(p->left->left) == RED) { // left left
		par = p->left;
		sib = p->left->left;
		return 1;
	}
	if (getColor(p->left) == RED && getColor(p->left->right) == RED) { // left right
		par = p->left;
		sib = p->left->right;
		return 2;
	}
	if (getColor(p->right) == RED && getColor(p->right->right) == RED) { // right right
		par = p->right;
		sib = p->right->right;
		return 3;
	}
	if (getColor(p->right) == RED && getColor(p->right->left) == RED) { // right left
		par = p->right;
		sib = p->right->left;
		return 4;
	}
	return 0; // all right, sib and par will be nullptr 
}
nodeRB* leftRotation(nodeRB* sib, nodeRB* par, RedBlackTree& rb) {
	nodeRB* t = sib->left;
	sib->left = par;
	sib->parent = par->parent;
	par->parent = sib;
	par->right = t;
	if (t)
		t->parent = par;
	if (rb.root == par) {
		rb.root = sib;
	}
	return sib; // return the new highest node, parent of this node is already changed inside this 
}
nodeRB* rightRotation(nodeRB* sib, nodeRB* par, RedBlackTree& rb) {
	nodeRB* t = sib->right;
	sib->right = par;
	sib->parent = par->parent;
	par->parent = sib;
	par->left = t;
	if (t)
		t->parent = par;
	if (rb.root == par) {
		rb.root = sib;
	}
	return sib; // return the new highest node
}
void swapColor(nodeRB* a, nodeRB* b) {
	bool c = getColor(a);
	assignColor(a, getColor(b));
	assignColor(b, c);
}
nodeRB* judgment(nodeRB* grandpar, RedBlackTree rb) { // check nullptr 
	nodeRB* par = nullptr;
	nodeRB* sib = nullptr;
	int sit = checkProb(grandpar, par, sib); // check the situation, par and sib is red
	if (getColor(grandpar->left) == RED && getColor(grandpar->right) == RED && sit != 0) { // uncle and parent are red
		assignColor(grandpar->left, BLACK);
		assignColor(grandpar->right, BLACK);
		assignColor(grandpar, RED);
		return grandpar;
	}
	// uncle is black
	if (sit == 1) { // left left
		swapColor(par, grandpar);
		return  rightRotation(par, grandpar, rb);
	}
	else if (sit == 2) { // left right 
		grandpar->left = leftRotation(sib, par, rb);
		swapColor(grandpar, grandpar->left);
		return rightRotation(grandpar->left, grandpar, rb);
	}
	else if (sit == 3) { // right right
		swapColor(par, grandpar);
		return  leftRotation(par, grandpar, rb);
	}
	else if (sit == 4) { // right left
		grandpar->right = rightRotation(sib, par, rb);
		swapColor(grandpar, grandpar->right);
		return leftRotation(grandpar->right, grandpar, rb);
	}
	else  // if black red, do nothing
		return grandpar;
}
nodeRB* pushNode(nodeRB* p, nodeRB* t, RedBlackTree rb) {
	if (!p) {
		p = t;
	}
	else {
		if (t->keyword > p->keyword) {
			p->right = pushNode(p->right, t, rb); // pass as a highest node 
			p->right->parent = p;
		}
		else {
			p->left = pushNode(p->left, t, rb);
			p->left->parent = p;
		}
		p = judgment(p, rb);
	}
	return p;
}
void initialize(RedBlackTree& RBTree) {
	RBTree.root = nullptr;
}

void destroyRBTree(nodeRB*& p) {
	if (p) {
		if (p->left) destroyRBTree(p->left);
		if (p->right) destroyRBTree(p->right);
		delete p;
		p = nullptr;
	}
}
nodeRB* searchRB(nodeRB* p, wstring key) {
	if (!p)
		return nullptr;
	if (p->keyword == key) {
		return p;
	}
	else if (p->keyword > key) {
		return searchRB(p->left, key);
	}
	else
		return searchRB(p->right, key);
}
void update(nodeRB* grandpar, bool isGrandparLeft) {
	if (grandpar->parent && isGrandparLeft) {
		grandpar->parent->left = grandpar;
	}
	else if (grandpar->parent && !isGrandparLeft) {
		grandpar->parent->right = grandpar;
	}
}
void fixDoubleBlack(nodeRB*& grandpar, bool isLeft, RedBlackTree& rb) {
	if (!grandpar)
		return;
	bool isGrandparLeft = (grandpar->parent && grandpar->parent->left == grandpar) ? true : false;
	nodeRB* uncle = (isLeft) ? grandpar->right : grandpar->left;
	if (!uncle) {
		return;
	}
	if (getColor(uncle) == BLACK) {
		if (isLeft) {
			if (getColor(uncle->right) == RED) { // right right 
				assignColor(uncle->right, BLACK);
				swapColor(uncle, grandpar);
				grandpar = leftRotation(uncle, grandpar, rb);
				update(grandpar, isGrandparLeft);
			}
			else if (getColor(uncle->left) == RED) { // right left
				assignColor(uncle->left, BLACK);
				uncle = rightRotation(uncle->left, uncle, rb);
				swapColor(uncle, grandpar);
				grandpar = leftRotation(uncle, grandpar, rb);
				update(grandpar, isGrandparLeft);
			}
			else { // all children of uncle is black
				assignColor(uncle, RED); // jump fix later, need mark the double black for grandpar here
				if (getColor(grandpar) == BLACK) {
					// become double black
					update(grandpar, isGrandparLeft);
					fixDoubleBlack(grandpar->parent, isGrandparLeft, rb);
				}
				else {
					assignColor(grandpar, BLACK);
				}
			}
		}
		else {
			if (getColor(uncle->left) == RED) { // left left
				assignColor(uncle->left, BLACK);
				swapColor(uncle, grandpar);
				grandpar = rightRotation(uncle, grandpar, rb);
				update(grandpar, isGrandparLeft);
			}
			else if (getColor(uncle->right) == RED) { // left right
				assignColor(uncle->right, BLACK);
				uncle = leftRotation(uncle->right, uncle, rb);
				swapColor(uncle, grandpar);
				grandpar = rightRotation(uncle, grandpar, rb);
				update(grandpar, isGrandparLeft);
			}
			else { // black black in all children of uncle
				assignColor(uncle, RED);
				if (getColor(grandpar) == BLACK) {
					// become double black
					update(grandpar, isGrandparLeft);
					fixDoubleBlack(grandpar->parent, isGrandparLeft, rb);

				}
				else {
					assignColor(grandpar, BLACK);
				}
			}
		}
	}
	else { // uncle red
		if (isLeft) {
			swapColor(uncle, grandpar);
			grandpar = leftRotation(uncle, grandpar, rb); // need mark the black
			update(grandpar, isGrandparLeft);
			fixDoubleBlack(grandpar->left, true, rb);
		}
		else {
			swapColor(uncle, grandpar);
			grandpar = rightRotation(uncle, grandpar, rb); // need mark the black
			update(grandpar, isGrandparLeft);
			fixDoubleBlack(grandpar->right, false, rb);

		}
	}
}
void deleteNodeRB(nodeRB*& p, wstring x, RedBlackTree& rb) { // p : parent, which is kept
	if (!p)
		return;
	if (p->keyword < x)
		deleteNodeRB(p->right, x, rb);
	else if (p->keyword > x)
		deleteNodeRB(p->left, x, rb);
	else { // 1 child
		if (p->left && !p->right) {
			if (getColor(p->left) == RED || getColor(p) == RED) { // parent and sib are not red at the same time
				p->keyword = p->left->keyword;
				p->meaning = p->left->meaning; 
				assignColor(p, BLACK);
				delete p->left;
				p->left = nullptr;
			}
			else { // parent and children are black
				nodeRB* par = p->parent; //p will be delete
				bool isLeft = (par->left == p) ? true : false; // p become double black
				p->keyword = p->left->keyword;
				p->meaning = p->left->meaning; 
				assignColor(p, BLACK);
				delete p->left;
				p->left = nullptr;
				fixDoubleBlack(par, isLeft, rb);
			}
		}
		else if (!p->left && p->right) {
			if (getColor(p->right) == RED || getColor(p) == RED) { // parent and sib are not red at the same time
				p->keyword = p->right->keyword;
				p->meaning = p->right->meaning;
				assignColor(p, BLACK);
				delete p->right;
				p->right = nullptr;
			}
			else { // parent and children are black
				nodeRB* par = p->parent; //p will be delete
				bool isLeft = (par->left == p) ? true : false; // p become double black
				p->keyword = p->right->keyword;
				p->meaning = p->right->meaning;
				assignColor(p, BLACK);
				delete p->right;
				p->right = nullptr;
				fixDoubleBlack(par, isLeft, rb);
			}
		}
		else if (!p->left && !p->right) { // 2 child black null
			if (p->color == RED || p == rb.root) {
				delete p;
				p = nullptr;
				return;
			}
			else {
				nodeRB* par = p->parent; //p will be delete
				bool isLeft = (par->left == p) ? true : false; // p become double black
				delete p;
				p = nullptr; // p become nullptr
				fixDoubleBlack(par, isLeft, rb);
			}
		}
		else if (p->left && p->right) {
			nodeRB* t = p->left;
			while (t->right)
				t = t->right;
			p->keyword = t->keyword;
			p->meaning = t->meaning; 
			deleteNodeRB(p->left, p->keyword, rb);
		}
	}
	return;
}
bool isTreeEmpty(RedBlackTree rb) {
	if (!rb.root)
		return true;
	else
		return false;
}
void traverseRB(nodeRB* p, wfstream& fo) {
	if (p) {
		traverseRB(p->left, fo);
		fo << p->keyword << " : " << p->meaning << endl;
		traverseRB(p->right, fo);
	}

}

void readFileRB(RedBlackTree& rb) {
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
		nodeRB* p = newRBNode(temp[pos].keyword, temp[pos].meaning);
		rb.root = pushNode(rb.root, p, rb);
		swapHE(temp[pos], temp[i]);
	}


	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
}
void writeFileRB(RedBlackTree rb) {
	wfstream fo(RESULT_SET, ios::out);
	// quickSort(dictionary, 0, size);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();

	traverseRB(rb.root, fo);

	cout << "Save to " << RESULT_SET << " sucessfully !\n";
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fo.close();
	system(RESULT_SET);

}
void findingWordRB(RedBlackTree rb) {
	wstring key;
	wcin.ignore();

	wfstream fi(INP_DESTINATION, ios::in);
	wfstream fo(OUT_DESTINATION, ios::out);
	cout << "Enter the word that you want to find in the " << INP_DESTINATION << ", output in the " << OUT_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, key);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	nodeRB* p = searchRB(rb.root, wformalize(key));
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


void insertingWordRB(RedBlackTree rb) {
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
	nodeRB* p = newRBNode(fil.keyword, fil.meaning);

	if (searchRB(rb.root, fil.keyword))
		cout << "Terminated, word is already exist!\n";
	else {
		nodeRB* p =  newRBNode(fil.keyword, fil.meaning); 
		rb.root = pushNode(rb.root, p, rb);
		cout << "Insert sucessfully!\n";
	}
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
}

void editingWordRB(RedBlackTree rb) {
	wstring temp;
	wcin.ignore();
	wfstream fi(INP_DESTINATION, ios::in);
	cout << "Enter the keyword and the new meaning that you want to edit in the " << INP_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, temp);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	hashElement fil = wfilter(temp);
	nodeRB* p = searchRB(rb.root, wformalize(fil.keyword));
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


void deletingWordRB(RedBlackTree rb) {
	wstring temp;
	wcin.ignore();
	wfstream fi(INP_DESTINATION, ios::in);
	cout << "Enter the word that you want to delete in the " << INP_DESTINATION << "\n";
	system(INP_DESTINATION);
	getline(fi, temp);
	duration<double, milli> ms_duration;
	auto st = steady_clock::now();
	temp = wformalize(temp);

	if (!searchRB(rb.root, temp))
		cout << "The keyword is not exist! \n";
	else {
		deleteNodeRB(rb.root, temp, rb);
		cout << "Deleted !\n";
	}
	auto en = steady_clock::now();
	ms_duration = en - st;
	cout << "\nRunning time : " << ms_duration.count() << endl;
	fi.close();
}